/*************************************************
 File name : socket.c
 Create date : 2013-11-25 06:19
 Modified date : 2013-11-25 06:19
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


int main(void)
{
	int sk;								//fd

	sk = socket(AF_INET, SOCK_STREAM, 0);

	if(sk==-1)
	{
		perror("socket");
		return -1;
	}

	//init服务器地址
	struct sockaddr_in servaddr;					//声明一个IPv4的地址类型	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9000);				//把端口号从主机字节序转换到网络字节序
	//servaddr.sin_addr.s_addr = inet_addr("192.168.1.227");		//绑定指定网卡地址
	servaddr.sin_addr.s_addr = INADDR_ANY;				//绑定本机所有网卡地址
	//inet_aton("192.168.1.227",&servaddr.sin_addr);			//ASCII to only IPv4
	//inet_pton(AF_INET,"192.168.1.227",&servaddr.sin_addr);		//protocol to network

	//bind绑定服务器地址
	int ret = bind(sk,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(ret == -1)
	{
		perror("bind");
		return -1;
	}
	
	//监听模式,被动模式
	ret = listen(sk,1000);
	if(ret == -1)
	{
		perror("listen");
		return -1;
	}

	//socket接受一个客户端连接
	struct sockaddr_in clientaddr;
	int addrlen = sizeof(clientaddr);
	int clientfd;

	while(1)
	{
		//一个新的已连接的socket:clientfd
		clientfd = accept(sk,(struct sockaddr *)&clientaddr,&addrlen);
		if(clientfd == -1)
		{
			perror("accept");
			continue;
		}
		printf("%s:%d\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
		write(clientfd,"hello,client\n",strlen("hello,client\n"));
	}

	return 0;
}
