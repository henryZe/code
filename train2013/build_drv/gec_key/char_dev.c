#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#include <linux/platform_device.h>

#include <plat/irqs.h>
#include <mach/irqs.h>


struct resource gec_key_res[] = 
{
	[0] = {
		.start = IRQ_EINT(16),
		.end   = IRQ_EINT(16),
		.name  = "key_1",
		.flags = IORESOURCE_IRQ,
	},
	
	[1] = {
		.start = IRQ_EINT(17),
		.end   = IRQ_EINT(17),
		.name  = "key_2",
		.flags = IORESOURCE_IRQ,
	},
	
	[2] = {
		.start = IRQ_EINT(18),
		.end   = IRQ_EINT(18),
		.name  = "key_3",
		.flags = IORESOURCE_IRQ,
	},
	
	[3] = {
		.start = IRQ_EINT(19),
		.end   = IRQ_EINT(19),
		.name  = "key_4",
		.flags = IORESOURCE_IRQ,
	},
	
	[4] = {
		.start = IRQ_EINT(24),
		.end   = IRQ_EINT(24),
		.name  = "key_5",
		.flags = IORESOURCE_IRQ,
	},
	
	[5] = {
		.start = IRQ_EINT(25),
		.end   = IRQ_EINT(25),
		.name  = "key_6",
		.flags = IORESOURCE_IRQ,
	},
	
	[6] = {
		.start = IRQ_EINT(26),
		.end   = IRQ_EINT(26),
		.name  = "key_7",
		.flags = IORESOURCE_IRQ,
	},
	
	[7] = {
		.start = IRQ_EINT(27),
		.end   = IRQ_EINT(27),
		.name  = "key_8",
		.flags = IORESOURCE_IRQ,
	},
	
};

void gec_dev_release(struct device *dev)
{
	printk(KERN_ALERT "gec dev release\n");
}

struct platform_device gec_dev = 
{
	.name = "gec_dev",
	.id   = -1,
	.dev  = 
	{
		.release = gec_dev_release,
	},
	.num_resources = ARRAY_SIZE(gec_key_res),
	.resource      = gec_key_res,
};


static int __init gec_dev_init(void)
{
	int error;

	//先注册设备
	error = platform_device_register(&gec_dev);
	if(error)
	{
		goto platform_device_register_err;
	}
	
	printk("platform device register OK\n");
	return 0;

platform_device_register_err:
	printk("platform device register failed\n");

	return -EFAULT;
}

static void __exit gec_dev_exit(void)
{
	platform_device_unregister(&gec_dev);
}


module_init(gec_dev_init);
module_exit(gec_dev_exit);

MODULE_AUTHOR("henry_Z");
MODULE_DESCRIPTION("char drivers");
MODULE_VERSION("v0.1");
MODULE_LICENSE("GPL");
