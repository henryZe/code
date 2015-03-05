/*************************************************
 File name : sig_lis.c
 Create date : 2013-12-12 20:26
 Modified date : 2013-12-12 20:26
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
#include <poll.h>
#include <netinet/ip.h>
#include <linux/icmp.h>
#include <netdb.h>


int sk;
void sig_recv(int sig);
int main(int argc,char *argv[])
{
	if(argc < 5)
	{
		printf("用法:udp localip localport remoteip remoteport\n");
		return -1;
	}

	int ret;
	int flags;

	//注册信号处理
	signal(SIGIO,sig_recv);

	sk = socket(AF_INET,SOCK_DGRAM,0);
	if(sk == -1)
	{
		perror("socket");
		return -1;
	}

	//激活socket的异步信号功能
	flags = fcntl(sk,F_GETFL);
	flags = flags|O_ASYNC;
	fcntl(sk,F_SETFL,flags);

	//让本进程成为socket的拥有者,信号只发送给这个拥有者进程 kill(pid,signal)
	fcntl(sk,F_SETOWN,getpid());

	//bind
	struct sockaddr_in localaddr = {0};
	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(atoi(argv[2]));
	localaddr.sin_addr.s_addr = inet_addr(argv[1]);
	
	ret = bind(sk,(struct sockaddr *)&localaddr,sizeof(localaddr));
	if(ret == -1)
	{
		perror("bind");
		return -1;
	}

	//初始化远程地址
	struct sockaddr_in remoteaddr = {0};
	remoteaddr.sin_family = AF_INET;
	remoteaddr.sin_port = htons(atoi(argv[4]));
	remoteaddr.sin_addr.s_addr = inet_addr(argv[3]);

	char sbuf[200] = {0};
	char buf[100] = {0};

	while(1)
	{
		bzero(buf,sizeof(buf));
		ret = read(0,buf,sizeof(buf)-1);

		if(ret > 0)
		{
			ret = sprintf(sbuf,"%s:%s\n\t%s",argv[1],argv[2],buf);
			sendto(sk,sbuf,ret,0,(struct sockaddr *)&remoteaddr,sizeof(remoteaddr));
		}
	}
	
	return 0;
}

void sig_recv(int sig)
{
	int  ret;
	char buf[200] = {0};

	bzero(buf,sizeof(buf));
	ret = recv(sk,buf,sizeof(buf)-1,0);

	if(ret > 0)
	{
		printf("%s\n",buf);
	}
}
