/*************************************************
 File name : server.c
 Create date : 2013-11-25 15:37
 Modified date : 2013-11-25 15:37
 Author : henryZ
 Email : henryZ_e@163.com
 
 ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>


#include "list.h"
#include "common.h"


struct server
{
	//监听sock
	int    tcpfd;
	struct sockaddr_in  tcpaddr;
	int    tcpaddrlen;
	struct node  *list_online;
	int    onlinecnt;
};

//客户线程信息
struct apt
{
	int    cltfd;
	struct sockaddr_in  cltaddr;
	int    cltaddrlen;
	pthread_t tid;
};

//服务器信息,全局变量
struct server server = {0};

int server_init()
{
	int sk;
	int ret;

	//创建基于TCP的SOCK
	sk = socket(AF_INET,SOCK_STREAM,0);
	if(sk == -1)
	{
		perror("socket");
		return -1;
	}
	server.tcpfd = sk;

	struct sockaddr_in servaddr;

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9000);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	//初始化服务器信息
	server.tcpaddr = servaddr;
	server.tcpaddrlen = sizeof(servaddr);

	//bind
	ret = bind(sk,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(ret == -1)
	{
		perror("bind");
		return -1;
	}

	//监听sk
	ret = listen(sk,1000);
	if(ret == -1)
	{
		perror("listen");
		return -1;
	}

	//初始化在线用户链表
	server.list_online = list_create(sizeof(struct clt));
	if(server.list_online == NULL)
	{
		perror("list create");
		return -1;
	}

	
	//创建用户数据目录
	if(mkdir("client_data/",0777) == -1)
	{
		perror("mkdir client_data");
	}

	return 0;
}


//register
int do_reg(struct apt *apt)
{
	int ret,fd;
	int ack = ACK_OK;
	struct clt clt = {0};

	send(apt->cltfd,&ack,sizeof(ack),0);

	//接受客户信息
	ret = recv(apt->cltfd,&clt,sizeof(clt),0);
	if(ret == sizeof(clt))
	{
		chdir("client_data/");

		//判断该CHAT号文件是否存在
		if(access(clt.chat,F_OK) != 0)
		{
			//文件不存在,则创建
			fd = open(clt.chat, O_WRONLY | O_CREAT,0777);
			if(fd != -1)
			{
				write(fd,&clt,sizeof(clt));
				ack = ACK_OK;
				send(apt->cltfd,&ack,sizeof(ack),0);
				
				printf("%s has been registed\n",clt.chat);
				
				chdir("../");
				return 0;
			}
		}
		else
		{
			ack = ACK_REP;
			send(apt->cltfd,&ack,sizeof(ack),0);
			chdir("../");
			return -1;
		}
	}

	//注册失败
	ack = ACK_ERR;
	send(apt->cltfd,&ack,sizeof(ack),0);
	chdir("../");
	return -1;
}


int cmp_chat(void *dat1, void *dat2)
{
	struct clt *clt1 = dat1;
	struct clt *clt2 = dat2;

	return strcmp(clt1->chat,clt2->chat);
}


int do_login(struct apt *apt)
{
	int ret,fd;
	int cmd;
	int ack = ACK_OK;
	struct clt clt = {0};
	struct clt tmp = {0};
	struct clt *who = NULL;
	struct node *find = NULL;

	send(apt->cltfd,&ack,sizeof(ack),0);

	ret = recv(apt->cltfd,&clt,sizeof(clt),0);
	if(ret == sizeof(clt))
	{
		chdir("client_data/");
		if(access(clt.chat,F_OK) == 0)
		{
			fd = open(clt.chat,O_RDONLY);
			if(fd != -1)
			{
				if(read(fd,&tmp,sizeof(tmp)) == sizeof(tmp))
				{
					printf("pass word:%s %s\n",tmp.pass,clt.pass);
					
					//用户认证成功
					if(strcmp(tmp.pass,clt.pass) == 0)
					{
						find = list_find(server.list_online, &clt, cmp_chat);
						if(find != NULL)
						{
							who = find->dat;
							//做踢人操作
							cmd = CMD_KILL;
							
							send(who->tcpfd, &cmd, sizeof(cmd), 0);
							close(who->tcpfd);
							server.onlinecnt--;
							
							find->prev->next = find->next;
							find->next->prev = find->prev;
							free(who);
							free(find);
						}
						//保存该用户的连接
						clt.tcpfd = apt->cltfd;
						//保存名字
						strcpy(clt.name,tmp.name);
						
						//只有通过登陆成功,才可以加入在线用户链表
						list_addtail(server.list_online, &clt);
						server.onlinecnt++;
						
						ack = ACK_OK;
						send(apt->cltfd, &ack, sizeof(ack), 0);
						//校验成功,将用户名字信息回送给客户端
						send(apt->cltfd, &clt, sizeof(clt), 0);
						
						printf("%s user log_in\n",clt.chat);
						
						chdir("../");
						return 0;
					}
				}
			}
			close(fd);
		}
		chdir("../");
	}

	ack = ACK_ERR;
	send(apt->cltfd, &ack, sizeof(ack), 0);
	return -1;
}


int do_del(struct apt *apt)
{
	int ret,fd;
	int cmd;
	int ack = ACK_OK;
	struct clt clt = {0};
	struct clt tmp = {0};

	//成功进入注销程序
	send(apt->cltfd,&ack,sizeof(ack),0);

	ret = recv(apt->cltfd,&clt,sizeof(clt),0);
	if(ret == sizeof(clt))
	{
		chdir("client_data/");
		if(access(clt.chat,F_OK) == 0)
		{
			ack = ACK_OK;
			//用户注册存在
			send(apt->cltfd, &ack, sizeof(ack), 0);
			
			fd = open(clt.chat,O_RDWR);
			if(fd != -1)
			{
				if(read(fd,&tmp,sizeof(tmp)) == sizeof(tmp))
				{
					printf("pass word:%s %s\n",tmp.pass,clt.pass);
					
					if(strcmp(tmp.pass,clt.pass) == 0)
					{
						ack = ACK_OK;
						//用户认证成功
						send(apt->cltfd, &ack, sizeof(ack), 0);
						
						ret = remove(clt.chat);
						
						if(ret == 0)
						{
							ack = ACK_OK;
							//用户注销动作成功
							send(apt->cltfd, &ack, sizeof(ack), 0);
							
							printf("%s user has been deleted\n",clt.chat);
							
							chdir("../");
							return 0;
						}
						
						else
						{
							ack = ACK_ERR;
							//用户注销动作失败
							send(apt->cltfd, &ack, sizeof(ack), 0);
							
							chdir("../");
							return -1;
						}
					}
					
					else
					{
						ack = ACK_ERR;
						//用户认证失败
						send(apt->cltfd, &ack, sizeof(ack), 0);
						
						chdir("../");
						return -1;
					}
				}
			}
		}
		
		else
		{
			ack = ACK_NON;
			//用户注册不存在
			send(apt->cltfd, &ack, sizeof(ack), 0);
			
			chdir("../");
			return -1;
		}
	}

	ack = ACK_ERR;
	send(apt->cltfd, &ack, sizeof(ack), 0);
	
	return -1;
}


int do_chat(struct apt *apt)
{
	int    cmd;
	int    ret;
	char   buf[100];
	char   sbuf[164];
	struct node *cur = NULL;
	struct clt  *clt = NULL;
	
	cmd = CMD_CHAT;

	//获取用户信息
	for(cur = (server.list_online)->next; cur != server.list_online; cur = cur->next)
	{
		clt = cur->dat;
		if(clt->tcpfd == apt->cltfd)
		{
			break;
		}
	}
		
	//准备发送的信息	
	bzero(buf,sizeof(buf));
	if(recv(apt->cltfd,buf,sizeof(buf)-1,0) > 0)
	{
		ret = sprintf(sbuf,"%s:\n%s",inet_ntoa(apt->cltaddr.sin_addr),buf);

		//转发给其他人
		for(cur = (server.list_online)->next; cur != server.list_online; cur = cur->next)
		{
			clt = cur->dat;
			if(clt->tcpfd != apt->cltfd)
			{
				send(clt->tcpfd,&cmd,sizeof(cmd),0);
				send(clt->tcpfd,sbuf,ret,0);
			}
		}
		
	}
	
	return 0;
}


int do_quit(struct apt *apt)
{
	struct node *cur;
	struct clt  *clt;
	
	for(cur = (server.list_online)->next; cur != server.list_online; cur = cur->next)
	{
		clt = cur->dat;
		if(clt->tcpfd == apt->cltfd)
		{
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			
			cur->next = NULL;
			cur->prev = NULL;
			
			printf("CHAT:%s user quit\n",clt->chat);
			
			free(cur->dat);
			free(cur);
			
			close(apt->cltfd);
			server.onlinecnt--;
			
			pthread_exit(NULL);
			return 0;
		}
	}
}


void *do_client(void *arg)
{
	int    ret;
	int    cmd;
	int    ack;
	struct apt *apt = arg;
	char   buf[100] = {0};
	char   sbuf[164] = {0};
	struct node *cur;
	struct clt  *clt;

	while(1)
	{
		//接受客户的连接
		if(recv(apt->cltfd,&cmd,sizeof(cmd),0) == sizeof(cmd))
		{
			switch(cmd)
			{
				//register
				case CMD_REG:
					do_reg(apt);
					close(apt->cltfd);
					pthread_exit(NULL);
					break;
				
				//log in
				case CMD_LOGIN:
					do_login(apt);
					break;
				
				//delete user
				case CMD_DEL:
					do_del(apt);
					close(apt->cltfd);
					pthread_exit(NULL);
					break;
				
				case CMD_CHAT:
					do_chat(apt);
					break;
				
				//quit
				case CMD_QUIT:
					do_quit(apt);
					break;
				
				
				default:
					ack = ACK_ERR;
					send(apt->cltfd,&ack,sizeof(ack),0);
					break;
			}
		}
		
		else
		{
			for(cur = (server.list_online)->next; cur != server.list_online; cur = cur->next)
			{
				clt = cur->dat;
				if(clt->tcpfd == apt->cltfd)
				{
					printf("%s user offline\n",clt->chat);
					break;
				}
			}
			if(cur == server.list_online)
			{
				printf("there is unregisted user was offline\n");
			}
			
			close(apt->cltfd);
			pthread_exit(NULL);
		}
	}
	
	return NULL;
}

void *do_information(void *arg)
{
	char buf[12];
	struct node *cur;
	struct clt *clt;
	DIR  *dir;
    struct dirent *dp;	

	while(1)
	{
		bzero(buf,sizeof(buf));
		fgets(buf,sizeof(buf)-1,stdin);
		
		if(strcmp(buf,"all\n") == 0)
		{
			dir = opendir("./client_data");
			while((dp = readdir(dir)) != NULL)
			{
				if((strcmp(dp->d_name,"..")&&(strcmp(dp->d_name,"."))) == 1)
				{
					printf("%s\t",dp->d_name);
				}
			}

			closedir(dir);
		}

		if(strcmp(buf,"onl\n") == 0)
		{
			for(cur = (server.list_online)->next; cur != server.list_online; cur = cur->next)
			{
				clt = cur->dat;
				printf("%s\t",clt->name);
			}
		}
	}
}

int main(void)
{
	//客户信息指针
	struct apt *apt = NULL;

	//初始化服务器
	if(server_init() != 0)
	{
		return -1;
	}

	pthread_t  dis_tid;
	pthread_create(&dis_tid,NULL,do_information,NULL);
	
	while(1)
	{
		//为客户线程分配空间
		apt = malloc(sizeof(*apt));
		if(apt == NULL)
		{
			sleep(1);
			perror("malloc");
			continue;
		}

		apt->cltaddrlen = sizeof(apt->cltaddr);
		apt->cltfd = accept(server.tcpfd,(struct sockaddr *)&(apt->cltaddr),&(apt->cltaddrlen));
		if(apt->cltfd == -1)
		{
			perror("accept");
			continue;
		}

		//创建客户服务线程
		pthread_create(&apt->tid,NULL,do_client,apt);
	}	
	
	return 0;
}
