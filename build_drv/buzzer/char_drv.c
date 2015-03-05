#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/delay.h>

#include <linux/fs.h>
#include <linux/cdev.h>

#include <asm/uaccess.h>

#include <linux/platform_device.h>
#include <plat/gpio-cfg.h>
#include <mach/gpio.h>

#include <linux/agpgart.h>

#include <linux/pwm.h>

#include "common.h"

#define NS_IN_1HZ	(1000000000UL)

struct pwm_device *pwm;
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

void pwm_switch(void)
{
	s3c_gpio_cfgpin(S5PV210_GPD0(0), S3C_GPIO_OUTPUT);
	
	pwm_config(pwm, 0, NS_IN_1HZ / 100);
	pwm_disable(pwm);

	gpio_set_value(S5PV210_GPD0(0),kernel_data.flag);
}

void buzzer_config(int arg)
{
	//CMP CNT 调整周期,改变占空比
	pwm_config(pwm, 10000000, NS_IN_1HZ/arg);
	pwm_enable(pwm);

	s3c_gpio_cfgpin(S5PV210_GPD0(0), S3C_GPIO_SFN(2));
}

void auto_buzzer(char arg)
{
	int i;

	switch(arg)
	{
		case 'i':
			for(i=1; i<101; i++)
			{
				buzzer_config(i);
				mdelay(100);
			}
			break;

		case 'd':	
			for(i=100; i>0; i--)
			{
				buzzer_config(i);
				mdelay(100);
			}
			break;

		default:
			printk("invalid input\n");
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
		case 1:
			pwm_switch();
			break;
		case 2:
			buzzer_config(kernel_data.argum);
			break;
		case 3:
			auto_buzzer(kernel_data.direct);
			break;
	}

	return 0;
}

static struct file_operations char_drv_fops = {
	.open = char_drv_open,
	.release = char_drv_close,

	.ioctl = char_drv_control,
};

int buzzer_init(void)
{
	int err;
	
	err = gpio_request(S5PV210_GPD0(0), "buzzer");	
	if(err)
	{
		printk("request GPIO for buzzer failed\n");
	}
	
	s3c_gpio_cfgpin(S5PV210_GPD0(0), S3C_GPIO_OUTPUT);
	gpio_set_value(S5PV210_GPD0(0), 0);

	pwm = pwm_request(0, "pwm");	
	if(IS_ERR(pwm))
	{
		printk("request PWM for buzzer failed\n");
		return -1;
	}
	pwm_config(pwm, 0, NS_IN_1HZ / 100);
	pwm_disable(pwm);

	return 0;
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

	buzzer_init();	

	return 0;
}

void buzzer_exit(void)
{	
	s3c_gpio_cfgpin(S5PV210_GPD0(0), S3C_GPIO_OUTPUT);
	gpio_set_value(S5PV210_GPD0(0), 0);
	
	gpio_free(S5PV210_GPD0(0));
	pwm_free(pwm);
}

void __exit char_drv_exit(void)
{
	printk("char_drv exit\n");
	
	cdev_del(&chardev.my_cdev);
	unregister_chrdev_region(chardev.dev_num, 1);

	buzzer_exit();
}


module_init(char_drv_init);
module_exit(char_drv_exit);

MODULE_AUTHOR("henry_Z");
MODULE_DESCRIPTION("char drivers");
MODULE_VERSION("v0.1");
MODULE_LICENSE("GPL");
