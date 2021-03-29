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


struct work_struct turn_off;

struct my_work_t {
	char   *name;
	struct work_struct turn_on;
};

struct my_work_t my_name;

struct tasklet_struct my_task;

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

void led_init(void)
{
	gpio_request(S5PV210_GPJ2(0),"led_0");
	
	gpio_direction_output(S5PV210_GPJ2(0),1);
}

int Thread_func(void *arg)
{
	printk("%s function\n",(char *)arg);
	return 0;
}

irqreturn_t Eint_16(int irq, void *dev_id)
{
	char *buf;
	buf = "thread";

	printk("Ext int 16 has come\n");
	
	//初始化速度最慢
	//kernel_thread(Thread_func, (void *)buf, CLONE_KERNEL);
	
	//速度居中
	schedule_work(&(my_name.turn_on));

	//小任务初始速度最快
	tasklet_schedule(&my_task);
	
	return IRQ_HANDLED;
}

irqreturn_t Eint_17(int irq, void *dev_id)
{
	printk("Ext int 17 has come\n");
	
	schedule_work(&turn_off);
	
	return IRQ_HANDLED;
}

void turnon_func(struct work_struct *work)
{
	struct my_work_t *p_name;
	
	printk("function: turn on\n");
	gpio_direction_output(S5PV210_GPJ2(0),0);
	
	//通过turn_on结构体找到my_work_t整个结构体
	p_name = container_of(work, struct my_work_t, turn_on);

	printk("The name is %s\n",p_name->name);
}

void turnoff_func(struct work_struct *work)
{
	printk("function: turn off\n");
	gpio_direction_output(S5PV210_GPJ2(0),1);
}

void tasklet_func(unsigned long arg)
{
	printk("Tasklet function number: %d\n", *(int *)arg);
}

static struct file_operations char_drv_fops = {
	.open = char_drv_open,
	.release = char_drv_close,

	
};


static int __init char_drv_init(void)
{
	int err;
	int req_irq16, req_irq17;
	//函数在init.text,将变量定义在堆里,这样变量才不会消失
	static int arg;
	arg = 10;

	my_name.name = "henryZ";
	
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

	req_irq16 = request_irq(IRQ_EINT(16), Eint_16, IRQF_TRIGGER_FALLING, "led0_on", NULL);
	req_irq17 = request_irq(IRQ_EINT(17), Eint_17, IRQF_TRIGGER_FALLING, "led0_off", NULL);

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

	tasklet_init(&my_task, tasklet_func, &arg);	
	
	INIT_WORK(&(my_name.turn_on), turnon_func);	
	INIT_WORK(&turn_off, turnoff_func);

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
