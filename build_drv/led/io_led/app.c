#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "common.h"

struct data_t user_on;
struct data_t user_off;


int main(int argc, char **argv)
{
	int fd,i;
	user_off.flag = 1;
	user_on.flag = 0;

	fd = open("/dev/char_dev",O_RDWR);
	if(fd < 0)
	{
		printf("open char_dev fail\n");
		return -1;
	}
	printf("open char_dev success\n");

	for(i=0;i<20;i++)
	{
		ioctl(fd, LED_0, &user_on);
		sleep(1);
		ioctl(fd, LED_1, &user_on);
		sleep(1);
		ioctl(fd, LED_2, &user_on);
		sleep(1);
		ioctl(fd, LED_3, &user_on);

		sleep(1);
		ioctl(fd, LED_0, &user_off);
		sleep(1);
		ioctl(fd, LED_1, &user_off);
		sleep(1);
		ioctl(fd, LED_2, &user_off);
		sleep(1);
		ioctl(fd, LED_3, &user_off);
		sleep(1);
	}
		
	
	close(fd);
	return 0;	
}
