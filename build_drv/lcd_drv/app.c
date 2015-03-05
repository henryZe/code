#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <linux/fb.h>


struct fb_var_screeninfo var;
int screen_size;
unsigned long *fb_mem;


int main()
{
	int fd,i,j,time;
	volatile unsigned int color = 0;
	
	fd = open("/dev/fb5", O_RDWR);
	if(fd<0)
	{
		perror("open");
	}
	
	ioctl(fd, FBIOGET_VSCREENINFO, &var);
	printf("var.xres = %d\n", var.xres);
	printf("var.yres = %d\n", var.yres);
	printf("var.bits_per_pixel = %d\n", var.bits_per_pixel);

	screen_size = var.xres * var.yres * (var.bits_per_pixel/8);

	//gec_fb_mmap的接口函数, 0表示由系统内核分配地址空间, 分配空间大小, 对内存访问权限, 修改内容会回写进内存影响其他进程
	fb_mem = (unsigned long *)mmap(0, screen_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if(!fb_mem)
	{
		printf("mmap error!\n");
	}


	for(time=0;time<0x7f;time++)
	{	
		for(i=0; i<480; i++)
		{
			for(j=0; j<800; j++)
			{
				*(fb_mem + i*800 + j) = color;
			}
		}

		color = color+0x10000;
		usleep(10000);
	}

	printf("color= %x\n",color);	
	
	for(time=0;time<0x7f;time++)
	{	
		for(i=0; i<480; i++)
		{
			for(j=0; j<800; j++)
			{
				*(fb_mem + i*800 + j) = color;
			}
		}
			
		color = color+0x10100;
		usleep(10000);
	}

	printf("color= %x\n",color);	

	for(time=0;time<0x7f;time++)
	{	
		for(i=0; i<480; i++)
		{
			for(j=0; j<800; j++)
			{
				*(fb_mem + i*800 + j) = color;
			}
		}
			
		color = color+0x101;
		usleep(10000);
	}
	
	printf("color= %x\n",color);	
	
	for(time=0;time<0x7f;time++)
	{	
		for(i=0; i<480; i++)
		{
			for(j=0; j<800; j++)
			{
				*(fb_mem + i*800 + j) = color;
			}
		}
			
		color = color+0x1;
		usleep(10000);
	}


	printf("color= %x\n",color);	

	printf("app has done.\n");	
	
	munmap(fb_mem, screen_size);
	close(fd);
	
	return 0;
}


