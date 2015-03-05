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

#include <linux/workqueue.h>

#include <linux/sched.h>


struct timer_list timer;


void timer_handler(unsigned long data)
{
	printk("timer function\n");
	printk("the arguments is %d\n",*(int *)data);

	//add_timer(&timer);
}

//非阻塞型
static int __init char_drv_init(void)
{
	static int a = 100;
	unsigned long timer_bef = jiffies;	
	unsigned long timer_aft = jiffies + 2*HZ;
	
	printk("char driver init\n");
	
	printk("timer_bef = %ld\n",timer_bef);
	printk("timer_aft = %ld\n",timer_aft);

	while(jiffies < timer_aft);
	
	init_timer(&timer);
	timer.expires = jiffies + 5*HZ;
	timer.function = timer_handler;
	timer.data = &a;

	//开始执行计时器	
	add_timer(&timer);
	
	return 0;
}

void __exit char_drv_exit(void)
{
	printk("char driver exit\n");
	del_timer(&timer);
}

module_init(char_drv_init);
module_exit(char_drv_exit);

MODULE_AUTHOR("henry_Z");
MODULE_DESCRIPTION("char drivers");
MODULE_VERSION("v0.1");
MODULE_LICENSE("GPL");
