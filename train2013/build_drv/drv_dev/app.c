#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char **argv)
{
	int fd;
	fd = open("/dev/gec_led1",O_RDWR);
	if(fd < 0)
	{
		printf("open gec_led1 fail\n");
		return -1;
	}
	printf("open gec_led1 success\n");

	int wnum = atoi(argv[1]);
	write(fd, &wnum, sizeof(wnum));	
	
	close(fd);
	return 0;	
}
