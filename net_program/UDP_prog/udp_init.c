/*************************************************
 File name : udp_init.c
 Create date : 2013-12-03 20:33
 Modified date : 2013-12-03 20:33
 Author : henryZ
 Email : henryZ_e@163.com
 
 ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <string.h>
#include <strings.h>


int main(int argc,char **argv)
{
	if(argc < 5)
	{
		printf("用法: udp localip localport remoteip remoteport\n");
		return -1;
	}

	int sk;
	int ret;

	//socket
	sk = socket(AF_INET,SOCK_DGRAM,0);
	if(sk == -1)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in  localaddr = {0};
	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(atoi(argv[2]));
	localaddr.sin_addr.s_addr = inet_addr(argv[1]);
	
	//bind
	ret = bind(sk,(struct sockaddr *)&localaddr,sizeof(localaddr));
	if(ret == -1)
	{
		perror("bind");
		return -1;
	}

	struct pollfd pfd[2];

	pfd[0].fd = 0;
	pfd[1].fd = sk;
	pfd[0].events = pfd[1].events = POLLIN;

	struct sockaddr_in remoteaddr = {0};
	remoteaddr.sin_family = AF_INET;
	remoteaddr.sin_port = htons(atoi(argv[4]));
	remoteaddr.sin_addr.s_addr = inet_addr(argv[3]);

	char sbuf[200] = {0};
	char buf[100] = {0};

	while(1)
	{
		//监视0与sk是否可读,阻塞类型
		ret = poll(pfd,2,-1);
		if(ret > 0)
		{
			//按位与,判断是否为零
			if(pfd[0].revents & POLLIN)
			{
				bzero(buf,sizeof(buf));
				ret = read(pfd[0].fd,buf,sizeof(buf)-1);

				if(ret > 0)
				{
					ret = sprintf(sbuf,"%s %s:\n\t%s",argv[1],argv[2],buf);
					sendto(sk,sbuf,ret,0,(struct sockaddr *)&remoteaddr,sizeof(remoteaddr));
				}
			}

			if(pfd[1].revents & POLLIN)
			{
				bzero(sbuf, sizeof(sbuf));
				ret = recv(sk, sbuf, sizeof(sbuf)-1, 0);

				if(ret > 0)
				{
					printf("%s",sbuf);
				}
			}
		}
	}
	return 0;
}
