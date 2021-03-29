#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "common.h"

struct data_t user_mode;


int main(int argc, char **argv)
{
	int fd,swi;

	fd = open("/dev/char_dev",O_RDWR);
	if(fd < 0)
	{
		printf("open char_dev fail\n");
		return -1;
	}
	printf("open char_dev success\n");

	switch(atoi(argv[1]))
	{
		case 0:	
			ioctl(fd, TURN_OFF, &user_mode);
			break;
		case 1:
			user_mode.direct = argv[2][0];
			ioctl(fd, TURN_ON, &user_mode);
			break;
		default:
			printf("invalid input\n");
			break;	
	}

	close(fd);
	return 0;	
}
