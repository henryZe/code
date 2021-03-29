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
	
	if(strcmp(argv[1],"write") == 0)
	{
		int wnum = atoi(argv[2]);
		write(fd, &wnum, sizeof(wnum));	
	}

	if(strcmp(argv[1],"read") == 0)
	{	
		int rnum;
		read(fd, &rnum, sizeof(rnum));

		printf("read val = %d\n",rnum);
	}
	
	close(fd);
	return 0;	
}
