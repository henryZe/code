/*************************************************
 File name : client.c
 Create date : 2013-11-27 01:27
 Modified date : 2013-11-27 01:27
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
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <setjmp.h>
#include <poll.h>

#include "common.h"



//定义跳转指令的环境变量,全局变量,包含信号掩码
sigjmp_buf jmp_showmenu;
int    servport = 9000;
char   servip[20] = {"192.168.0.100"};
struct sockaddr_in  servaddr;
struct clt clt = {0};

const char *menu[] = {
	"1-登录",
	"2-注册",
	"3-注销",
	"4-退出",
};


int  client_init()
{
	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(servport);
	inet_pton(AF_INET,servip,&servaddr.sin_addr);

	return 0;
}


void get_string(char *tip, char *buf, int size, int must)
{
	do
	{
		printf("%s",tip);
		if(fgets(buf,size,stdin) != NULL)
		{
			buf[strlen(buf)-1] = '\0';
			if(strlen(buf) > 0)
			{
				break;
			}
		}
	}while(must);
}


//显示主菜单
int show_menu()
{
	int  i;
	int  op;
	char buf[3];

	for(i=0; i < sizeof(menu)/sizeof(menu[0]); i++)
	{
		printf("\t%s\n",menu[i]);
	}

	get_string("请输入你的选择",buf,3,1);
	op = atoi(buf);

	return op;
}


int connect_server()
{
	int sk;
	int ret;

	sk = socket(AF_INET,SOCK_STREAM,0);
	if(sk == -1)
	{
		perror("socket");
		return -1;
	}

	ret = connect(sk,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(ret == -1)
	{
		perror("connect");
		return -1;
	}

	return sk;
}


//信号中断程序
void sig_showmenu(int sig)
{
	int cmd = CMD_QUIT;

	send(clt.tcpfd,&cmd,sizeof(cmd),0);
	close(clt.tcpfd);
	//信号掩码1
	siglongjmp(jmp_showmenu,1);
}


int do_reg(int sk)
{
	int cmd = CMD_REG;
	int ack;
	int ret;

	//连接服务器
	sk = connect_server();
	if(sk == -1)
	{
		printf("连接服务器失败\n");
		return -1;
	}

	bzero(&clt,sizeof(clt));
	get_string("请输入你的姓名",clt.name,sizeof(clt.name),1);
	get_string("请输入你的CHAT",clt.chat,sizeof(clt.chat),1);
	get_string("请输入你的密码",clt.pass,sizeof(clt.pass),1);
	get_string("请输入你的性别",clt.sex,sizeof(clt.sex),0);

	//发送注册信号
	send(sk,&cmd,sizeof(cmd),0);

	ret = recv(sk,&ack,sizeof(ack),0);
	if(ret == sizeof(ack))
	{
		//服务器允许注册
		if(ack == ACK_OK)
		{
			send(sk,&clt,sizeof(clt),0);
			
			ret = recv(sk,&ack,sizeof(ack),0);
			if(ret == sizeof(ack))
			{
				if(ack == ACK_OK)
				{
					printf("%s 注册成功\n",clt.name);
					return 0;
				}
				
				else if(ack == ACK_REP)
				{
					printf("%s 用户CHAT重复\n",clt.name);
					
					close(sk);
					return -1;
				}
			}
		}
	}

	printf("%s 注册失败\n",clt.name);

	close(sk);
	return -1;
}


int do_chat(int sk)
{
	int    ret;
	int    cmd;
	struct pollfd pfd[2];
	char   buf[200] = {0};

	signal(SIGINT,sig_showmenu);
	pfd[0].fd = 0;
	pfd[1].fd = sk;
	pfd[0].events = pfd[1].events = POLLIN;

	while(1)
	{
		//阻塞等待
		ret = poll(pfd,2,-1);
		if(ret > 0)
		{
			if(pfd[0].revents & POLLIN)
			{
				bzero(buf,sizeof(buf));
				sprintf(buf,"%s:\n\t",clt.name);
				if(read(0,(buf+strlen(buf)),(sizeof(buf)-1-strlen(buf))) > 0)
				{
					cmd = CMD_CHAT;
					send(sk,&cmd,sizeof(cmd),0);
					send(sk,buf,strlen(buf),0);
				}
			}

			if(pfd[1].revents & POLLIN)
			{
				if(recv(sk,&cmd,sizeof(cmd),0) == sizeof(cmd))
				{
					if(cmd == CMD_CHAT)
					{
						bzero(buf,sizeof(buf));
						if(recv(sk,buf,sizeof(buf),0) > 0)
						{
							printf("%s",buf);
						}
					}
					
					else if(cmd == CMD_KILL)
					{
						close(sk);
						printf("%s 你在另外一个地方登录了\n",clt.name);
						return 0;
					}
				}
			}
		}
	}
}


int do_login(int sk)
{
	int cmd = CMD_LOGIN;
	int ack;

	sk = connect_server();
	if(sk == -1)
	{
		printf("连接服务器失败\n");
		return -1;
	}

	bzero(&clt,sizeof(clt));
	get_string("请输入你的CHAT",clt.chat,sizeof(clt.chat),1);
	get_string("请输入你的密码",clt.pass,sizeof(clt.pass),1);

	send(sk,&cmd,sizeof(cmd),0);

	if(recv(sk,&ack,sizeof(ack),0) == sizeof(ack))
	{
		if(ack == ACK_OK)
		{
			send(sk,&clt,sizeof(clt),0);

			if(recv(sk,&ack,sizeof(ack),0) == sizeof(ack))
			{
				if(ack == ACK_OK)
				{
					recv(sk,&clt,sizeof(clt),0);
					
					printf("%s 登录成功\n",clt.name);
					clt.tcpfd = sk;
					do_chat(sk);
					close(sk);
					return 0;
				}
			}
		}
	}
	
	printf("%s 登录失败\n",clt.name);
	close(sk);
	return -1;
}


int do_del(int sk)
{
	int cmd = CMD_DEL;
	int ack;
	
	sk = connect_server();
	if(sk == -1)
	{
		printf("连接服务器失败\n");
		return -1;
	}

	bzero(&clt,sizeof(clt));
	get_string("请输入你想注销的CHAT",clt.chat,sizeof(clt.chat),1);
	get_string("请输入该CHAT的密码",clt.pass,sizeof(clt.pass),1);

	send(sk,&cmd,sizeof(cmd),0);
	
	//成功进入注销程序
	if(recv(sk,&ack,sizeof(ack),0) == sizeof(ack))
	{
		if(ack == ACK_OK)
		{
			send(sk,&clt,sizeof(clt),0);
			
			//用户注册存在
			if(recv(sk,&ack,sizeof(ack),0) == sizeof(ack))
			{
				if(ack == ACK_OK)
				{
					//用户认证成功
					if(recv(sk,&ack,sizeof(ack),0) == sizeof(ack))
					{
						if(ack == ACK_OK)
						{
							//用户注销动作成功
							if(recv(sk,&ack,sizeof(ack),0) == sizeof(ack))
							{
								if(ack == ACK_OK)
								{
									printf("%s 注销成功\n",clt.chat);
									close(sk);
									return 0;
								}
								
								else
								{
									printf("%s 注销失败\n",clt.chat);
									close(sk);
									return -1;
								}
							}
						}
						
						else if(ack == ACK_ERR)
						{
							printf("%s 用户认证失败\n",clt.chat);
							close(sk);
							return -1;
						}
					}
				}
				
				else if(ack == ACK_NON)
				{
					printf("%s 用户注册不存在\n",clt.chat);
					close(sk);
					return -1;
				}
			}
		}
	}
	
	printf("%s 注销失败\n",clt.chat);
	close(sk);
	return -1;
}


int main(int argc,char **argv)
{
	int sk;
	int op;
	int ret;
	int cmd;

	//如果指定服务器地址
	if(argc >= 3)
	{
		strcpy(servip,argv[1]);
		servport = atoi(argv[2]);
	}

	//初始化客户端
	if(client_init() != 0)
	{
		return -1;
	}

	//设置包含信号跳转点,将当前的信号掩码一并保存进环境变量中
	sigsetjmp(jmp_showmenu,1);
	
	//忽略Ctrl+C的信号
	signal(SIGINT,SIG_IGN);

	while(1)
	{
		switch((op = show_menu()))
		{
			case 1:
				//登录
				do_login(sk);
				break;

			case 2:
				//注册
				do_reg(sk);
				break;

			case 3:
				//注销
				do_del(sk);
				break;

			case 4:
				cmd = CMD_QUIT;
				send(clt.tcpfd,&cmd,sizeof(cmd),0);
				close(clt.tcpfd);
				return 0;

			default:
				printf("%d 无效选择\n",op);
				break;
		}
	}

	return 0;
}
