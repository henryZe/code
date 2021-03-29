#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "common.h"

#define LEVEL1 1300
#define LEVEL2 2600


int main(int argc, char **argv)
{
	struct data_t turn_slow;
	struct data_t turn_fast;
	struct data_t turn_flash;
	struct data_t turn_on;
	struct data_t turn_off;
	
	turn_slow.flag = 0;
	turn_fast.flag = 1;
	turn_flash.flag= 2;
	turn_off.flag  = 0;
	turn_on.flag   = 1;
	
	
	int fd;
	fd = open("/dev/char_dev",O_RDWR);
	if(fd < 0)
	{
		printf("open char_dev fail\n");
		return -1;
	}
	printf("open char_dev success\n");

	int adc_num;
	
	while(1)
	{
		read(fd, &adc_num, sizeof(adc_num));
		printf("ADC: %d\n", adc_num);
	
		if((adc_num>=0)&&(adc_num<=LEVEL1))
		{
			ioctl(fd, BUZZER, &turn_off);
			ioctl(fd, LED, &turn_slow);
		}
	
		else if((adc_num>LEVEL1)&&(adc_num<=LEVEL2))
		{
			ioctl(fd, BUZZER, &turn_off);
			ioctl(fd, LED, &turn_fast);
		}
	
		else if(adc_num>LEVEL2)
		{
			ioctl(fd, BUZZER, &turn_on);
			ioctl(fd, LED, &turn_flash);
		}
	}

	close(fd);
	return 0;	
}
