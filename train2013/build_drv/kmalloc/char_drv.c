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
#include <linux/interrupt.h>

#include <linux/slab.h>
#include <linux/vmalloc.h>

char *str1 = NULL;
char *str2 = NULL;

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

static struct file_operations char_drv_fops = {
	.open = char_drv_open,
	.release = char_drv_close,	
};


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

	str1 = (char *)kmalloc(100,GFP_KERNEL);
	memset(str1,0,100);
	strcpy(str1,"kmalloc work\n");
	printk("%s",str1);
	
	str2 = (char *)vmalloc(100);
	memset(str2,0,100);
	strcpy(str2,"vmalloc work\n");
	printk("%s",str2);
	
	return 0;
}

void __exit char_drv_exit(void)
{
	printk("char_drv exit\n");
	
	cdev_del(&chardev.my_cdev);
	unregister_chrdev_region(chardev.dev_num, 1);
	
	kfree(str1);
	vfree(str2);
}

module_init(char_drv_init);
module_exit(char_drv_exit);

MODULE_AUTHOR("henry_Z");
MODULE_DESCRIPTION("char drivers");
MODULE_VERSION("v0.1");
MODULE_LICENSE("GPL");
