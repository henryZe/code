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

	//SOCK_DGRAM=>UDP  SOCK_STREAM=>TCP  SOCK_RAW=>ICMP
	sk = socket(AF_INET, SOCK_DGRAM, 0);
	if(sk == -1)
	{
		perror("socket");
		return -1;
	}

	//绑定目标地址,端口号是重点
	struct sockaddr_in target = {0};
	target.sin_family = AF_INET;	
	target.sin_port = htons(2000);
	target.sin_addr.s_addr = inet_addr("0.0.0.0"); 
	//target.sin_addr.s_addr = INADDR_ANY; 
	if(bind(sk, (struct sockaddr *)&target, sizeof(target)) == -1)
	{
		perror("bind");
		return -1;
	}

	char buf[100] = {0};
	struct sockaddr_in who = {0};
	int    addrlen = sizeof(who);
	
	//receive
	while(1)	
	{
		bzero(buf, sizeof(buf));
		//ret = recv(sk, buf, sizeof(buf) - 1, 0);
		ret = recvfrom(sk, buf, sizeof(buf) - 1, 0, (struct sockaddr *)&who, &addrlen);
		if(ret > 0)
		{
			printf("%s\n", buf);
			//系统自动分配服务器一个端口号
			printf("send by %s:%d\n",inet_ntoa(who.sin_addr),ntohs(who.sin_port));
		}
	}

	return 0;
}
