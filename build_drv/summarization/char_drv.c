#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/cdev.h>

#include <asm/uaccess.h>

#include <linux/delay.h>

#include <linux/platform_device.h>
#include <plat/gpio-cfg.h>
#include <mach/gpio.h>

#include <linux/ioport.h>
#include <asm/io.h>

#include <linux/interrupt.h>
#include <linux/wait.h>

#include "common.h"


wait_queue_head_t my_wait;

int  kernel_val;
int  flag = 0;
int  led_flag = 1;

int  dev_id;

unsigned long *vaddr, *vaddr1;
unsigned long *rTSADCCON0,*rTSDATX0,*rADCMUX,*rCLRINTADC0,*rGPJ2DAT,*rGPJ2CON;

struct mydev_t {
	int major,minor;
	dev_t dev_num;
	
	struct cdev my_cdev;
};

struct mydev_t chardev;
struct data_t kernel_data;


void led_run(int msec)
{
	while(led_flag)
	{	
		int i;
		for(i=0; i<4; i++)
		{	
			iowrite8(~(0x1<<i), rGPJ2DAT);
			mdelay(msec);
		}
	}
}

void led_flash(void)
{
	while(led_flag)
	{
		iowrite8(0x0,rGPJ2DAT);
		mdelay(500);	
		iowrite8(0xf,rGPJ2DAT);
		mdelay(500);	
	}
}

int led(struct data_t *data)
{
	led_flag = 1;
	switch(data->flag)
	{
		case 0:
			led_run(700);
			break;
		case 1:
			led_run(200);
			break;
		case 2:
			led_flash();
			break;
	}
	
	return 0;
}

int buzzer(struct data_t *data)
{
	gpio_set_value(S5PV210_GPD0(0),data->flag);
	
	return 0;
}

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
	unsigned long read;

	printk("char drv read\n");

	//开启ADC
	read = ioread32(rTSADCCON0);
	read |= (1<<0);
	iowrite32(read, rTSADCCON0);

	//等待开启并转化完成
	wait_event_interruptible(my_wait, flag!=0);

	//精度12bits
	kernel_val = (int)(ioread32(rTSDATX0) & (0xfff));
	flag = 0;
	
	read = copy_to_user((void *)buf, &kernel_val, count);
	if(read)
	{
		printk("read fail\n");
		return -1;
	}	

	return 0;
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
			led_flag = 0;
			led(&kernel_data);
			break;
		case 1:
			buzzer(&kernel_data);
			break;
	}

	return 0;
}

static struct file_operations char_drv_fops = {
	.open = char_drv_open,
	.release = char_drv_close,

	.read = char_drv_read,

	.ioctl = char_drv_control,
};

irqreturn_t adc1_int(int irqno, void *dev_id)
{
	int val;

	flag = 1;
	
	val = ioread32(rCLRINTADC0)|0x1;
	iowrite32(val,rCLRINTADC0);
	
	wake_up_interruptible(&my_wait);

	return IRQ_HANDLED;
}

int adc_init(void)
{
	int ret;	

	if(!request_mem_region(0xE1700000, 0x20, "adc"))
	{
		printk("request mem failed\n");
		return -EBUSY;
	}

	vaddr = (unsigned long *)ioremap(0xE1700000, 0x20);

	rTSADCCON0 = vaddr;
	rTSDATX0 = vaddr+3;
	rCLRINTADC0 = vaddr+6;
	rADCMUX = vaddr+7;
	
	//片选
	iowrite8(0x0, rADCMUX);

	//enable分频
	iowrite32((1<<14)|(65<<6)|(1<<16), rTSADCCON0);

	ret = request_irq(IRQ_ADC, adc1_int, IRQF_DISABLED|IRQF_SHARED, "adc_irq", &dev_id);
	if(ret)
	{
		//显示中断号
		printk("request irq[%d] failed\n", S5P_IRQ_VIC2(23));
		return -EBUSY;
	}

	init_waitqueue_head(&my_wait);
	
	return 0;	
}

int led_init(void)
{
	if(!request_mem_region(0xe0200280, 0x8, "led"))
	{
		printk("request mem failed\n");
		return -EBUSY;
	}

	vaddr1 = (unsigned long *)ioremap(0xe0200280, 0x8);

	rGPJ2CON = vaddr1;
	rGPJ2DAT = vaddr1+1;

	iowrite32(0x1111,rGPJ2CON);
	iowrite32(0xf,rGPJ2DAT);

	return 0;
}

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

	gec_class = class_create(THIS_MODULE, "gec_adc")

	adc_init();	
	led_init();
	buzzer_init();

	return 0;
}

void adc_exit(void)
{		
	iounmap(vaddr);
	release_mem_region(0xE1700000, 0x20);

	free_irq(IRQ_ADC, &dev_id);
}

void buzzer_exit(void)
{
	gpio_set_value(S5PV210_GPD0(0), 0);
	gpio_free(S5PV210_GPD0(0));
}

void led_exit(void)
{		
	iounmap(vaddr1);
	release_mem_region(0xe0200280, 0x8);
}

void __exit char_drv_exit(void)
{
	//unregister_chrdev(250, "char_dev");	

	cdev_del(&chardev.my_cdev);
	unregister_chrdev_region(chardev.dev_num, 1);

	adc_exit();
	buzzer_exit();
	led_exit();
	
	printk("char_drv exit\n");
}


module_init(char_drv_init);
module_exit(char_drv_exit);

MODULE_AUTHOR("henry_Z");
MODULE_DESCRIPTION("char drivers");
MODULE_VERSION("v0.1");
MODULE_LICENSE("GPL");
