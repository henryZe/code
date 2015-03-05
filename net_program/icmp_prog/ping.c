/*************************************************
 File name : ping.c
 Create date : 2013-12-04 04:59
 Modified date : 2013-12-04 04:59
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


int  seq = 1;
unsigned short  checksum(unsigned short *buf,int len);
int  send_icmp(int sk,struct sockaddr_in *target);
int  proc_packet(char *buf,int len);

int main(int argc,char **argv)
{
	int    sk;
	struct protoent *pent = NULL;
	struct hostent  *hent = NULL;
	struct sockaddr_in  target = {0};

	if(argc < 2)
	{
		printf("用法:ping remoteip\n");
		return -1;
	}
/*
   	//打印所有协议号
	while(pent = getprotoent())
	{
		printf("%s %d\n",pent->p_name,pent->p_proto);
	}
*/

	//获取ICMP的协议号	
	pent = getprotobyname("icmp");
	if(pent == NULL)
	{
		perror("getproto");
		return -1;
	}
	struct ip *iphdr;

	//创建基于ICMP的socket SOCK_RAW
	sk = socket(AF_INET,SOCK_RAW,pent->p_proto);
	if(sk == -1)
	{
		perror("socket icmp");
		return -1;
	}

	//ASCII ==> IP address
	target.sin_addr.s_addr = inet_addr(argv[1]);
	if(target.sin_addr.s_addr == ((unsigned int)-1))
	{
		//解析域名
		hent = gethostbyname(argv[1]);
		if(hent == NULL)
		{
			perror("gethost");
			return -1;
		}

		memcpy(&target.sin_addr.s_addr, hent->h_addr, hent->h_length);

		
		char **ptr = NULL;
		for(ptr = hent->h_addr_list;*ptr != NULL; ptr++)
		{
			memcpy(&target.sin_addr.s_addr,*ptr,hent->h_length);
			printf("%s\n",inet_ntoa(target.sin_addr));
		}
		
	}

	printf("the first addr:%s\n",inet_ntoa(target.sin_addr));

	//发送ICMP包
	int ret;
	struct pollfd  pfd[1];

	pfd[0].fd = sk;
	pfd[0].events = POLLIN;

	while(1)
	{
		send_icmp(sk,&target);

		//无限监听等待
		ret = poll(pfd,1,-1);
		if(ret > 0)
		{
			if(pfd[0].revents & POLLIN)
			{
				char buf[200] = {0};
				struct sockaddr_in  remoteaddr = {0};
				int addrlen = sizeof(remoteaddr);

				//接受ICMP包
				ret = recvfrom(sk,buf,sizeof(buf),0,(struct sockaddr *)&remoteaddr,&addrlen);
				if(ret > 0)
				{
					proc_packet(buf,ret);
				}
			}
		}
	}
	
	return 0;
}


int send_icmp(int sk,struct sockaddr_in *target)
{
	char buf[200] = {0};
	struct icmphdr *hdr = (struct icmphdr *)buf;
	struct timeval  tv;
	int  len;
	int  ret;

	hdr->type = 8;
	hdr->code = 0;
	hdr->checksum = 0;

	hdr->un.echo.id = getpid();
	hdr->un.echo.sequence = seq;
	//全局变量
	seq++;

	gettimeofday(&tv,NULL);
	memcpy(buf+sizeof(*hdr),&tv,sizeof(tv));

	//16 = 8+8
	len = sizeof(*hdr) + sizeof(tv);

	//计算校验和
	hdr->checksum = checksum((unsigned short *)buf,len);

	ret = sendto(sk,buf,len,0,(struct sockaddr *)target,sizeof(*target));
	return ret;
}


int proc_packet(char *buf,int len)
{
	//IP首部,20字节
	struct ip *iphdr = NULL;
	//ICMP首部,8字节
	struct icmphdr *hdr = NULL;
	int    iplen = 0;
	double diff;
	double tmp;
	struct timeval tv,*ptv;
	char   pbuf[100] = {0};

	//IP首部
	iphdr = (struct ip *)buf;
	//ip_hl是以4个字节为单位
	printf("iphdr len = %d\n",iphdr->ip_hl*4);

	if(iphdr->ip_p != IPPROTO_ICMP)
	{
		printf("It is not a ICMP packet.\n");
		return -1;
	}

	//ICMP首部
	//buf是char型
	hdr = (struct icmphdr *)(buf + iphdr->ip_hl*4);
	//0模式,0代码为PING的应答模式
	if((hdr->type != 0)||(hdr -> code != 0))
	{
		printf("It is not a PING reply.\n");
		return -1;
	}

	gettimeofday(&tv,NULL);
	tmp = tv.tv_sec*1000 + tv.tv_usec/1000;
	ptv = (struct timeval *)(buf + iphdr->ip_hl*4 + sizeof(*hdr));
	
	diff = tmp - (ptv->tv_sec*1000 + ptv->tv_usec/1000);
	
	sprintf(pbuf,"%d bytes from %s: icmp_req=%d ttl=%d time=%f ms\n",len-iphdr->ip_hl*4,inet_ntoa(iphdr->ip_src),hdr->un.echo.sequence,iphdr->ip_ttl,diff);
	printf("%s",pbuf);

	return 0;
}

//计算校验和
unsigned short  checksum(unsigned short *buf,int len)
{
	unsigned int sum = 0;

	while(len > 1)
	{
		sum += *buf;
		buf++;
		//short型两个字节
		len -= 2;
	}
	
	if(len == 1)
	{
		sum += *(unsigned char *)buf;
	}

	//高16位+低16位 = short型
	sum = (sum >> 16)+(sum & 0xffff);
	sum += (sum >> 16);

	//sum取反
	return ~sum;
}
