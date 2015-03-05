/*************************************************
 File name : select_lis.c
 Create date : 2013-11-26 03:09
 Modified date : 2013-11-26 03:09
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


int main()
{
	int mouse;
	int flags;
	int ret;

	mouse = open("/dev/input/mice",O_RDONLY);
	if(mouse == -1)
	{
		perror("open error");
		return -1;
	}

	fd_set rset;
	struct timeval tv;

	char buf[100];
	while(1)
	{
		FD_ZERO(&rset);					//循环清零
		FD_SET(0,&rset);				//设置监听文件0
		FD_SET(mouse,&rset);				//设置监听鼠标

		tv.tv_sec = 5;
		tv.tv_usec = 0;					//us

		ret = select(mouse+1,&rset,NULL,NULL,&tv);	//监听个数
		if(ret>0)
		{
			if(FD_ISSET(0,&rset))
			{
				bzero(buf,sizeof(buf));

				if(read(0,buf,sizeof(buf)-1)>0)
				{
					printf("keyboard say:%s",buf);
				}
			}

			if(FD_ISSET(mouse,&rset))
			{
				bzero(buf,sizeof(buf));

				if(read(mouse,buf,sizeof(buf)-1)>0)
				{
					printf("mouse say:%s\n",buf);
				}
			}

		}
		else
		{
			printf("超时\n");
		}
	}
	return 0;
}
