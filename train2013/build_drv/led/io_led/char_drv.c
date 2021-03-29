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

void led_0(struct data_t *turn)
{
	switch(turn->flag)
	{
		case 0:
			gpio_direction_output(S5PV210_GPJ2(0),0);
			break;
		case 1:
			gpio_direction_output(S5PV210_GPJ2(0),1);
			break;
	}
}

void led_1(struct data_t *turn)
{
	switch(turn->flag)
	{
		case 0:
			gpio_direction_output(S5PV210_GPJ2(1),0);
			break;
		case 1:
			gpio_direction_output(S5PV210_GPJ2(1),1);
			break;
	}
}

void led_2(struct data_t *turn)
{
	switch(turn->flag)
	{
		case 0:
			gpio_direction_output(S5PV210_GPJ2(2),0);
			break;
		case 1:
			gpio_direction_output(S5PV210_GPJ2(2),1);
			break;
	}
}

void led_3(struct data_t *turn)
{
	switch(turn->flag)
	{
		case 0:
			gpio_direction_output(S5PV210_GPJ2(3),0);
			break;
		case 1:
			gpio_direction_output(S5PV210_GPJ2(3),1);
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
			led_0(&kernel_data);
			break;
		case 1:
			led_1(&kernel_data);
			break;
		case 2:
			led_2(&kernel_data);
			break;
		case 3:
			led_3(&kernel_data);
			break;
	}

	return 0;
}

static struct file_operations char_drv_fops = {
	.open = char_drv_open,
	.release = char_drv_close,

	.ioctl = char_drv_control,
};

void led_init(void)
{
	gpio_request(S5PV210_GPJ2(0),"led_0");
	gpio_request(S5PV210_GPJ2(1),"led_1");
	gpio_request(S5PV210_GPJ2(2),"led_2");
	gpio_request(S5PV210_GPJ2(3),"led_3");
	
	gpio_direction_output(S5PV210_GPJ2(0),1);
	gpio_direction_output(S5PV210_GPJ2(1),1);
	gpio_direction_output(S5PV210_GPJ2(2),1);
	gpio_direction_output(S5PV210_GPJ2(3),1);
}


static int __init char_drv_init(void)
{
	int err;
	
	printk("char_drv init\n");

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

	led_init();	

	return 0;
}

void led_exit(void)
{		
	gpio_free(S5PV210_GPJ2(0));
	gpio_free(S5PV210_GPJ2(1));
	gpio_free(S5PV210_GPJ2(2));
	gpio_free(S5PV210_GPJ2(3));
}

void __exit char_drv_exit(void)
{
	printk("char_drv exit\n");
	
	cdev_del(&chardev.my_cdev);
	unregister_chrdev_region(chardev.dev_num, 1);

	led_exit();
}


module_init(char_drv_init);
module_exit(char_drv_exit);

MODULE_AUTHOR("henry_Z");
MODULE_DESCRIPTION("char drivers");
MODULE_VERSION("v0.1");
MODULE_LICENSE("GPL");
