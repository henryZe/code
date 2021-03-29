#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char **argv)
{
	int fd;
	fd = open("/dev/char_dev",O_RDWR);
	if(fd < 0)
	{
		printf("open char_dev fail\n");
		return -1;
	}
	printf("open char_dev success\n");

	int wnum = atoi(argv[1]);
	write(fd, &wnum, sizeof(wnum));	
	
	close(fd);
	return 0;	
}
