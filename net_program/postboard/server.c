#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main(void)
{
	int sk;
	int ret;
	int on = 1;

	//socket
	sk = socket(AF_INET, SOCK_DGRAM, 0);
	if(sk == -1)
	{
		perror("socket");
		return -1;
	}

	//设置socket操作,使能广播
	setsockopt(sk,SOL_SOCKET,SO_BROADCAST,&on,sizeof(on));

	//bind,绑定目标地址
	struct sockaddr_in target = {0};
	target.sin_family = AF_INET;	
	target.sin_port = htons(2000);
	target.sin_addr.s_addr = inet_addr("255.255.255.255"); 

	char buf[100] = {0};
	
	//send
	while(1)	
	{
		bzero(buf, sizeof(buf));
		sprintf(buf,"Good morning!");
		sendto(sk,buf,sizeof(buf),0,(struct sockaddr*)&target,sizeof(target));
		sleep(1);
	}

	return 0;
}
