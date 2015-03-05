#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

struct input_event  key_value;


int main(int argc, char **argv)
{
	int fd;
	fd = open("/dev/event1",O_RDWR);
	if(fd < 0)
	{
		printf("open event1 fail\n");
		return -1;
	}
	printf("open event1 success\n");

	for(;;)
	{
		read(fd, &key_value, sizeof(struct input_event));	
		printf("key_value.type = %d\n",key_value.type);
		printf("key_value.code = %d\n",key_value.code);
		printf("key_value.value = %d\n",key_value.value);
		printf("\n");
	}
	
	close(fd);
	return 0;	
}
