/*************************************************
 File name : poll_listen.c
 Create date : 2013-11-26 02:49
 Modified date : 2013-11-26 02:49
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

int main(int argc,char **argv)
{
	int mouse;
	int flags;
	int ret;

	mouse = open("/dev/input/mice",O_RDONLY);
	if(mouse == -1)
	{
		perror("open mouse");
		return -1;
	}

	struct pollfd pfd[2];

	pfd[0].fd = 0;
	pfd[1].fd = mouse;
	pfd[0].events = pfd[1].events = POLLIN;			//监听输入

	char buf[100];
	while(1)
	{
		ret = poll(pfd,2,atoi(argv[1]));				//ms
		if(ret > 0)
		{
			if(pfd[0].revents == POLLIN)		//如果键盘有输入
			{
				bzero(buf,sizeof(buf));

				if(read(0,buf,sizeof(buf)-1)>0)
				{
					printf("keyboard say:%s",buf);
				}
			}
			
			if(pfd[1].revents == POLLIN)
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
