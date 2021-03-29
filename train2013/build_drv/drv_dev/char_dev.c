#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#include <linux/platform_device.h>

#include <mach/irqs.h>
#include <plat/irqs.h>


void gec_led_dev_release(struct device *dev)
{
	printk("gec_led_dev_release\n");
}

struct resource gec_led_resource[] =
{
	[0] = { 
	   	.start = 0xe0200280,  
	   	.end   = 0xe0200280+3, 
	   	.name  = "GPJ2CON",
	   	.flags = IORESOURCE_MEM
	},
	 
	[1] = { 
		.start = 0xe0200284,  
	   	.end   = 0xe0200284+3, 
	   	.name  = "GPJ2DAT",
	   	.flags = IORESOURCE_MEM
	},

	[2] = {
		.start = IRQ_EINT(16),
		.end   = IRQ_EINT(16),
		.name  = "KEY_1",
		.flags = IORESOURCE_IRQ
	},

};

struct platform_device  gec_led_dev =
{
	.name = "gec_led",
	//无后缀名
	.id   = -1,
	.dev  = 
	{
		.release = gec_led_dev_release,
	},
	.num_resources = ARRAY_SIZE(gec_led_resource),
	.resource      =  gec_led_resource,
};

static int __init gec_dev_init(void)
{
	int ret;
	//设备注册
	ret = platform_device_register(&gec_led_dev);
	if(ret)
	{
		goto platform_device_register_err;
	}
	
	return 0;

platform_device_register_err:
	printk(KERN_ERR "platform_device_register failed!\n");
	return ret;
}

static void __exit gec_dev_exit(void)
{
	platform_device_unregister(&gec_led_dev);
}


module_init(gec_dev_init);
module_exit(gec_dev_exit);

MODULE_AUTHOR("henry_Z");
MODULE_DESCRIPTION("char device");
MODULE_VERSION("v0.1");
MODULE_LICENSE("GPL");
