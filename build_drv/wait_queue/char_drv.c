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

#include <linux/wait.h>


wait_queue_head_t my_wait;

static int kernel_val;
static int flag = 0;

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

ssize_t char_drv_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
	int err;	

	printk("char_drv_read\n");
	
	if(count < 0)
	{
		return -1;
	}
	
	//条件不符合,则进入等待队列
	wait_event_interruptible(my_wait, flag!=0);
	
	err = copy_to_user(buf, &kernel_val, count);
	if(err)
	{
		printk("copy to user failed\n");
	}
	
	flag = 0;
	return 0;
}

void led_init(void)
{
	gpio_request(S5PV210_GPJ2(0),"led_0");
	
	gpio_direction_output(S5PV210_GPJ2(0),1);
}

irqreturn_t Eint_16(int irq, void *dev_id)
{
	printk("Ext int 16 has come\n");
		
	gpio_direction_output(S5PV210_GPJ2(0),0);
	
	kernel_val = 16;
	flag = 1;
	
	wake_up_interruptible(&my_wait);
	
	return IRQ_HANDLED;
}

irqreturn_t Eint_17(int irq, void *dev_id)
{
	printk("Ext int 17 has come\n");
		
	gpio_direction_output(S5PV210_GPJ2(0),1);
	
	kernel_val = 17;
	flag = 1;
	
	wake_up_interruptible(&my_wait);
	
	return IRQ_HANDLED;
}

static struct file_operations char_drv_fops = {
	.open = char_drv_open,
	.release = char_drv_close,
	
	.read = char_drv_read,
	
};


static int __init char_drv_init(void)
{
	int err;
	int req_irq16, req_irq17;
	
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

	req_irq16 = request_irq(IRQ_EINT(16), Eint_16, IRQF_TRIGGER_FALLING|IRQF_PROBE_SHARED, "led0_on", NULL);
	req_irq17 = request_irq(IRQ_EINT(17), Eint_17, IRQF_TRIGGER_FALLING|IRQF_PROBE_SHARED, "led0_off", NULL);

	if(req_irq16)
	{
		printk("request irq Ext_int16 fail\n");
		return -1;
	}
	
	if(req_irq17)
	{
		printk("request irq Ext_int17 fail\n");
		return -1;
	}

	led_init();
	init_waitqueue_head(&my_wait);	

	return 0;
}

void led_exit(void)
{		
	gpio_free(S5PV210_GPJ2(0));
}

void __exit char_drv_exit(void)
{
	printk("char_drv exit\n");
	
	cdev_del(&chardev.my_cdev);
	unregister_chrdev_region(chardev.dev_num, 1);

	free_irq(IRQ_EINT(16),NULL);
	free_irq(IRQ_EINT(17),NULL);

	led_exit();
	
	
}

module_init(char_drv_init);
module_exit(char_drv_exit);

MODULE_AUTHOR("henry_Z");
MODULE_DESCRIPTION("char drivers");
MODULE_VERSION("v0.1");
MODULE_LICENSE("GPL");
