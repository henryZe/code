#include <linux/module.h>
#include <linux/init.h>
#include <linux/input.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/cdev.h>

#include <asm/uaccess.h>

#include <linux/platform_device.h>
#include <plat/gpio-cfg.h>
#include <mach/gpio.h>

#include <linux/ioport.h>
#include <asm/io.h>

#include <linux/interrupt.h>
#include <mach/irqs.h>
#include <plat/irqs.h>

static struct input_dev *button_dev;


static irqreturn_t button_interrupt(int irq, void *data)
{
	//汇报键值,键值为BTN_0,状态value为:
	//1表示按下
	input_report_key(button_dev, BTN_0, 1);
	//0表示弹起
	input_report_key(button_dev, BTN_0, 0);
	//同步事件
	input_sync(button_dev);
	
	return IRQ_HANDLED;
}

static int __init button_init(void)
{
	int error;

	if(request_irq(IRQ_EINT(16), button_interrupt, IRQF_DISABLED|IRQF_TRIGGER_FALLING, "button", NULL))
	{
		printk("request irq failed\n");
		return -EBUSY;
	}


	//分配空间
	button_dev = input_allocate_device();
	if(!button_dev)
	{
		printk(KERN_ERR "input allocate failed\n");
		error = -ENOMEM;
		goto err_free_irq;
	}


	button_dev->name = "gec_key";

	//设备信息id
	button_dev->id.bustype = 0x1234;
	button_dev->id.vendor  = 0x1234;
	button_dev->id.product = 0x1234;
	button_dev->id.version = 0x1234;
	
	//使能按键事件
	button_dev->evbit[0] = BIT_MASK(EV_KEY);
	//使能BTN_0按键,只有使能过才允许使用
	button_dev->keybit[BIT_WORD(BTN_0)] = BIT_MASK(BTN_0);


	//注册输入设备
	error = input_register_device(button_dev);	
	if(error)
	{
		printk("input device register failed\n");
		goto err_free_dev;
	}

	return 0;


err_free_dev:
	input_free_device(button_dev);
err_free_irq:
	free_irq(IRQ_EINT(16), NULL);

	return error;
}

static void __exit button_exit(void)
{
	input_free_device(button_dev);
	
	free_irq(IRQ_EINT(16), NULL);
}


module_init(button_init);
module_exit(button_exit);

MODULE_AUTHOR("henry_Z");
MODULE_DESCRIPTION("char drivers");
MODULE_VERSION("v0.1");
MODULE_LICENSE("GPL");
