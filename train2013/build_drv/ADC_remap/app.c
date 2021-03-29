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

	int rnum;
	read(fd, &rnum, sizeof(rnum));
	printf("ADC: %d\n",rnum);
	
	close(fd);
	return 0;	
}
