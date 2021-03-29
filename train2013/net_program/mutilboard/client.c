/*************************************************
 File name : client.c
 Create date : 2013-12-04 22:19
 Modified date : 2013-12-04 22:19
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

	//UDP
	sk = socket(AF_INET,SOCK_DGRAM,0); 
	if(sk == -1)
	{
		perror("socket");
		return -1;
	}

	//bind本地地址,多播组只发送给端口2000
	struct sockaddr_in  localaddr = {0};
       	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(2000);
	localaddr.sin_addr.s_addr = INADDR_ANY;

	ret = bind(sk,(struct sockaddr *)&localaddr,sizeof(localaddr));
	if(ret == -1)
	{
		perror("bind");
		return -1;
	}

	//加入多播组,将本地IP地址附入
	struct ip_mreq  group = {0};
	group.imr_multiaddr.s_addr = inet_addr("224.0.0.2");
	group.imr_interface.s_addr = INADDR_ANY;
	
	//设置socket操作,加入多播组成员
	ret = setsockopt(sk,IPPROTO_IP,IP_ADD_MEMBERSHIP,&group,sizeof(group));
	if(ret == -1)
	{
		perror("setsockopt add_membership");
		return -1;
	}

	char buf[100];
	while(1)
	{
		bzero(buf,sizeof(buf));
		ret = recv(sk,buf,sizeof(buf)-1,0);
		if(ret > 0)
		{
			printf("%s",buf);
		}
	}

	return 0;
}

