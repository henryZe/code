#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>


int main(int argc, char **argv)
{
	int fd;
	int read_val;

	fd = open("/dev/char_dev",O_RDWR);
	if(fd < 0)
	{
		printf("open char_dev fail\n");
		return -1;
	}
	printf("open char_dev success\n");
		
	read(fd, &read_val, sizeof(int));
	printf("key:%d\n", read_val);	
		
	close(fd);
	return 0;	
}
