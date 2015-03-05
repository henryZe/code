#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/cdev.h>

#include <asm/uaccess.h>

#include <linux/platform_device.h>
#include <plat/gpio-cfg.h>
#include <mach/gpio.h>

#include <linux/agpgart.h>

#include <linux/ioport.h>
#include <asm/io.h>

#include "common.h"

struct data_t kernel_data;

struct mydev_t {
	int major,minor;
	dev_t dev_num;
	
	struct cdev my_cdev;
};

struct mydev_t chardev;


static int char_drv_open(struct inode *inod, struct file *filp)
{
	printk("char_drv_open\n");
	return 0;
}

static int char_drv_close(struct inode *inod, struct file *filp)
{
	printk("char_drv_close\n");
	return 0;
}

void DC_stop(void)
{
	gpio_direction_output(S5PV210_GPJ3(0),0);
	gpio_direction_output(S5PV210_GPH2(3),0);
}

void DC_run(char direct)
{
	switch(direct)
	{
		case 'r':
			gpio_direction_output(S5PV210_GPJ3(0),0);
			gpio_direction_output(S5PV210_GPH2(3),1);
			printk("right run\n");
			break;
		case 'l':
			gpio_direction_output(S5PV210_GPJ3(0),1);
			gpio_direction_output(S5PV210_GPH2(3),0);
			printk("left run\n");
			break;
	}
}

static int char_drv_control(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
	int err;	

	printk("char_drv_ioctrl\n");
	
	if(_IOC_TYPE(cmd) != WON_MAGIC)
	{
		printk("your magic number is error\n");
		return -1;
	}

	err = copy_from_user(&kernel_data, (struct data_t *)arg, sizeof(struct data_t));

	if(err)
	{
		printk("gain command fail\n");
	}

	switch(_IOC_NR(cmd))
	{
		case 0:
			DC_stop();
			break;
		case 1:
			DC_run(kernel_data.direct);
			break;
	}

	return 0;
}

static struct file_operations char_drv_fops = {
	.open = char_drv_open,
	.release = char_drv_close,

	.ioctl = char_drv_control,
};

int DC_init(void)
{
	s3c_gpio_cfgpin(S5PV210_GPJ3(0), S3C_GPIO_SFN(0x1));	
	s3c_gpio_cfgpin(S5PV210_GPH2(3), S3C_GPIO_SFN(0x1));	

	gpio_request(S5PV210_GPJ3(0),"DC_+");
	gpio_request(S5PV210_GPH2(3),"DC_-");
/*
	if(!request_mem_region(0xe0200024, 0x4, "DC_motor"))
	{
		printk("request mem failed\n");
		return -EBUSY;
	}
	
	rGPA1PUD = (unsigned long *)ioremap(0xe0200024, 0x4);
	iowrite32(0xa,rGPA1PUD);*/
	
	s3c_gpio_setpull(S5PV210_GPJ3(0),S3C_GPIO_PULL_UP);
	s3c_gpio_setpull(S5PV210_GPH2(3),S3C_GPIO_PULL_UP);

	printk("request GPA0 success\n");
	
	DC_stop();
	
	return 0;
}


static int __init char_drv_init(void)
{
	int err;
	
	printk("DC_motor init\n");

	chardev.major = 0;
	chardev.minor = 0;
	chardev.dev_num = MKDEV(chardev.major,chardev.minor);

	err = alloc_chrdev_region(&chardev.dev_num, 0, 1, "char_dev");

	if(err)
	{
		printk("char device region fail\n");
		return -1;
	}

	cdev_init(&chardev.my_cdev, &char_drv_fops);
	cdev_add(&chardev.my_cdev, chardev.dev_num, 1);

	printk("char device region success\n");

	DC_init();	

	return 0;
}

void DC_exit(void)
{		
	gpio_free(S5PV210_GPJ3(0));
	gpio_free(S5PV210_GPH2(3));
}

void __exit char_drv_exit(void)
{
	printk("char_drv exit\n");
	
	cdev_del(&chardev.my_cdev);
	unregister_chrdev_region(chardev.dev_num, 1);

	DC_exit();
}


module_init(char_drv_init);
module_exit(char_drv_exit);

MODULE_AUTHOR("henry_Z");
MODULE_DESCRIPTION("char drivers");
MODULE_VERSION("v0.1");
MODULE_LICENSE("GPL");
