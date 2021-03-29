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

#include <mach/irqs.h>
#include <plat/irqs.h>

#include <linux/interrupt.h>


int  kernel_val;

unsigned long *rGPJ2CON,*rGPJ2DAT;

struct mydev_t {
	int major,minor;
	dev_t dev_num;
	
	struct cdev my_cdev;
};

struct mydev_t chardev;

struct class *gec_class;

struct resource *ledcon_r, *leddat_r, *ledcon_reg, *leddat_reg, *key1_r;
int  key1_ret;


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
	int val;
	
	printk("char_drv_write\n");
	
	write = copy_from_user(&kernel_val, buf, count);
	if(write)
	{
		printk("write fail\n");
		return -1;
	}

	light = kernel_val/10-1;
	turn = kernel_val%10;

	val = ioread32(rGPJ2DAT);
	switch(turn)
	{
		case 0:
			val &= ~(1<<light);
			break;	
		case 1:
			val |= (1<<light);
			break;
	}
	iowrite32(val, rGPJ2DAT);
	
	return 0;
}

static struct file_operations char_drv_fops = {
	.open = char_drv_open,
	.release = char_drv_close,

	.write = char_drv_write,

	//.ioctrl = char_drv_control,
};

irqreturn_t key_1(int irq, void *dev_id)
{
	printk("Ext int 16 has come\n");
	
	return IRQ_HANDLED;
}

int led_init(struct platform_device *pdev)
{
	ledcon_r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	leddat_r = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	key1_r   = platform_get_resource(pdev, IORESOURCE_IRQ, 0);

	if(!ledcon_r || !leddat_r || !key1_r)
	{
		printk("platform get resource failed\n");
		return -EFAULT;
	}
	
	ledcon_reg = request_mem_region(ledcon_r->start, resource_size(ledcon_r), ledcon_r->name);
	leddat_reg = request_mem_region(leddat_r->start, resource_size(leddat_r), leddat_r->name);
	key1_ret   = request_irq(key1_r->start, key_1, IRQF_TRIGGER_FALLING|IRQF_PROBE_SHARED, "key_1", NULL);

	if(!ledcon_reg || !leddat_reg)
	{
		printk("request mem failed\n");
		return -EBUSY;
	}
	
	if(key1_ret)
	{
		printk("request irq failed\n");
		return -1;
	}

	rGPJ2CON = (unsigned long *)ioremap(ledcon_reg->start, resource_size(ledcon_reg));
	rGPJ2DAT = (unsigned long *)ioremap(leddat_reg->start, resource_size(leddat_reg));
	
	printk("IO remap success\n");

	iowrite32(0x1111,rGPJ2CON);
	iowrite32(0xf,rGPJ2DAT);

	return 0;	
}


static int gec_drv_probe(struct platform_device *pdev)
{
	int err;
	
	printk("gec_drv probe\n");

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

	gec_class = class_create(THIS_MODULE, "gec_led");
	if(!gec_class)
	{
		printk("class_create err\n");
		return -EFAULT;
	}

	//class, *parent, dev_t, *drvdata, const char *fmt
	device_create(gec_class, NULL, chardev.dev_num, NULL, "gec_led%d", 1);
	
	printk("make device node success\n");

	led_init(pdev);	

	return 0;
}

void led_exit(void)
{		
	iounmap(rGPJ2CON);
	iounmap(rGPJ2DAT);

	release_mem_region(ledcon_reg->start, resource_size(ledcon_reg));
	release_mem_region(leddat_reg->start, resource_size(leddat_reg));
}

int gec_drv_remove(struct platform_device *pdev)
{
	printk("gec_drv remove\n");

	cdev_del(&chardev.my_cdev);
	unregister_chrdev_region(chardev.dev_num, 1);

	led_exit();
	
	return 0;
}

struct platform_driver  gec_led_drv =
{
	.probe  = gec_drv_probe,
	.remove = gec_drv_remove,
	.driver =
	{
		.name = "gec_led",
	},
};

static int __init gec_drv_init(void)
{
	int ret;
	//驱动注册
	ret = platform_driver_register(&gec_led_drv);
	if(ret)
	{
		goto platform_driver_register_err;
	}
	return 0;

platform_driver_register_err:
	printk(KERN_ERR "platform_driver_register failed!\n");
	return ret;
}

static void __exit gec_drv_exit(void)
{
	platform_driver_unregister(&gec_led_drv);
}


module_init(gec_drv_init);
module_exit(gec_drv_exit);

MODULE_AUTHOR("henry_Z");
MODULE_DESCRIPTION("char drivers");
MODULE_VERSION("v0.1");
MODULE_LICENSE("GPL");
