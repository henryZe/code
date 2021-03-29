#include <linux/module.h>
#include <linux/init.h>
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
#include <linux/wait.h>

struct class *gec_class;

wait_queue_head_t my_wait;

int  kernel_val;

int arg;

unsigned long *vaddr,*vaddr1;
unsigned long *rTSADCCON0,*rTSDATX0,*rADCMUX,*rCLRINTADC0,*rGPH2CON,*rGPH2DAT;

struct mydev_t {
	int major,minor;
	dev_t dev_num;
	
	struct cdev my_cdev;
};

struct mydev_t chardev;


static int char_drv_open(struct inode *inod, struct file *filp)
{
	//开启
	

	printk("char_drv_open\n");
	return 0;
}

static int char_drv_close(struct inode *inod, struct file *filp)
{
	//关闭
	

	printk("char_drv_close\n");
	return 0;
}

ssize_t char_drv_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
	unsigned long read;
	int val;

	printk("char drv read\n");

	//开启ADC
	read = ioread32(rTSADCCON0);
	read |= (1<<0);
	iowrite32(read, rTSADCCON0);
		
	while((*rTSADCCON0)&(0x1<<0));
		
	val = ioread32(rCLRINTADC0)|0x1;
	iowrite32(val,rCLRINTADC0);

	//精度12bits
	kernel_val = (int)(ioread32(rTSDATX0) & (0xfff));
	
	read = copy_to_user((void *)buf, &kernel_val, count);
	if(read)
	{
		printk("read fail\n");
		return -1;
	}	

	return 0;
}

static struct file_operations char_drv_fops = {
	.open = char_drv_open,
	.release = char_drv_close,

	.read = char_drv_read,
};

int adc_init(void)
{
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
	
	//气体传感器开关初始化
	gpio_request(S5PV210_GPH2(0),"DCOUT");
    s3c_gpio_cfgpin(S5PV210_GPH2(0),3);
	
	//片选
	iowrite8(0x0, rADCMUX);

	//enable分频
	iowrite32((1<<14)|(65<<6)|(1<<16), rTSADCCON0);

	init_waitqueue_head(&my_wait);
	
	return 0;	
}


static int __init char_drv_init(void)
{
	int err;
	
	printk("char_drv init\n");

	chardev.major = 0;
	chardev.minor = 0;
	chardev.dev_num = MKDEV(chardev.major,chardev.minor);

	err = alloc_chrdev_region(&chardev.dev_num, 0, 1, "gas_num");

	if(err)
	{
		printk("char device region fail\n");
		return -1;
	}

	cdev_init(&chardev.my_cdev, &char_drv_fops);
	cdev_add(&chardev.my_cdev, chardev.dev_num, 1);

	printk("char device region success\n");

	gec_class = class_create(THIS_MODULE, "gec_gassensors");
	if(!gec_class)
	{
		printk("class_create err\n");
		return -EFAULT;
	}

	//class, *parent, dev_t, *drvdata, const char *fmt
	device_create(gec_class, NULL, chardev.dev_num, NULL, "gec_gassensor");
	printk("make device node success\n");
	
	adc_init();	

	return 0;
}

void adc_exit(void)
{		
	iounmap(vaddr);
	release_mem_region(0xE1700000, 0x20);
	
	gpio_free(S5PV210_GPH2(0));
}

void __exit char_drv_exit(void)
{
	cdev_del(&chardev.my_cdev);
	unregister_chrdev_region(chardev.dev_num, 1);

	adc_exit();
	
	printk("char_drv exit\n");
}


module_init(char_drv_init);
module_exit(char_drv_exit);

MODULE_AUTHOR("henry_Z");
MODULE_DESCRIPTION("char drivers");
MODULE_VERSION("v0.1");
MODULE_LICENSE("GPL");
