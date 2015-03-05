/*************************************************
 File name : server.c
 Create date : 2013-12-04 22:19
 Modified date : 2013-12-05 05:07
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


int main(void)
{
	int sk;
	int ret;
	int bit;

	//UDP
	sk = socket(AF_INET,SOCK_DGRAM,0); 
	if(sk == -1)
	{
		perror("socket");
		return -1;
	}

	//指定多播组的地址,只发送给多播组成员的端口2000
	struct sockaddr_in muladdr = {0};
	muladdr.sin_family = AF_INET;
	muladdr.sin_port = htons(2000);
	//D类地址224.0.0.1开始,组播地址
	muladdr.sin_addr.s_addr = inet_addr("224.0.0.2");

	
	//获得本身服务器的IP地址
	struct sockaddr_in srvaddr = {0};
       	int  srvlen = sizeof(srvaddr);

	srvaddr.sin_family = AF_INET;
//	srvaddr.sin_port = htons(7700);
	srvaddr.sin_addr.s_addr = inet_addr("192.168.1.226");

	bind(sk,(struct sockaddr *)&srvaddr,srvlen);	


	char *ptr = "Good morning,guys!";
	char buf1[100] = {0};
	char buf2[100] = {0};


	//填充buf,准备发送
	ret = sprintf(buf1,"%s\n",ptr);
	while(1)
	{
		//UDP => sendto
		sendto(sk,buf1,ret,0,(struct sockaddr *)&muladdr,sizeof(muladdr));
	
		//sendto之后才可以获取本机IP
		getsockname(sk,(struct sockaddr *)&srvaddr,&srvlen);
		bit = sprintf(buf2,"send by %s:%d\n",inet_ntoa(srvaddr.sin_addr),ntohs(srvaddr.sin_port));
		sendto(sk,buf2,bit,0,(struct sockaddr *)&muladdr,sizeof(muladdr));

		sleep(1);
	}

	return 0;
}

