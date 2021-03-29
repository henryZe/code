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


int main(int argc,char **argv)
{
	int  servport = 9000;
	char servip[20] = {"127.0.0.1"};
	int  sk;
	int  ret;

	if(argc >= 3)
	{
		strcpy(servip,argv[1]);
		servport = atoi(argv[2]);
	}

	sk = socket(AF_INET,SOCK_STREAM,0);
	if(sk == -1)
	{
		perror("socket");
		return -1;
	}

	//init服务器地址
	struct sockaddr_in servaddr;					//声明一个IPv4的地址类型	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(servport);				//把端口号从主机字节序转换到网络字节序
	//servaddr.sin_addr.s_addr = inet_addr("192.168.1.227");		//绑定指定网卡地址
	//servaddr.sin_addr.s_addr = INADDR_ANY;				//绑定本机所有网卡地址
	//inet_aton("192.168.1.227",&servaddr.sin_addr);			//ASCII to only IPv4
	inet_pton(AF_INET,servip,&servaddr.sin_addr);		//protocol to network

	//CONNECT
	ret = connect(sk,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(ret == -1)
	{
		perror("connect");
		return -1;
	}
	
	printf("connect ok\n");

	//READ
	char buf[100] = {0};
	ret = read(sk,buf,sizeof(buf)-1);
	if(ret > 0)
	{
		printf("%s",buf);
	}

	return 0;
}
