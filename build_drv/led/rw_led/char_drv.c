#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/cdev.h>

#include <asm/uaccess.h>

#include <linux/platform_device.h>
#include <plat/gpio-cfg.h>
#include <mach/gpio.h>

int  kernel_val;

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

ssize_t char_drv_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
	unsigned long write;
	int light,turn;
	
	printk("char_drv_write\n");
	
	write = copy_from_user(&kernel_val, buf, count);
	if(write)
	{
		printk("write fail\n");
		return -1;
	}

	light = kernel_val/10-1;
	turn = kernel_val%10;

	gpio_direction_output(S5PV210_GPJ2(light),turn);

	return 0;
}

static struct file_operations char_drv_fops = {
	.open = char_drv_open,
	.release = char_drv_close,

	.write = char_drv_write,

	//.ioctrl = char_drv_control,
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

//	register_chrdev(250, "char_dev", &char_drv_fops);
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
	
	//unregister_chrdev(250, "char_dev");	

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
