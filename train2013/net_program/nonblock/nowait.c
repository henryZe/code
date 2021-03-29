/*************************************************
 File name : nowait.c
 Create date : 2013-11-26 02:27
 Modified date : 2013-11-26 02:27
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


int main()
{
	int mouse;
	int flags;

	mouse = open("/dev/input/mice",O_RDONLY|O_NONBLOCK);
	if(mouse == -1)
	{
		perror("open mouse");
		return -1;
	}

	flags = fcntl(0,F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(0,F_SETFL,flags);

	char buf[100];
	while(1)
	{
		bzero(buf,sizeof(buf));
		if(read(0,buf,sizeof(buf)-1)>0)
		{
			printf("keyboard say:%s",buf);
		}

		bzero(buf,sizeof(buf));
		if(read(mouse,buf,sizeof(buf)-1)>0)
		{
			printf("mouse say:%s\n",buf);
		}
	}
	return 0;
}





