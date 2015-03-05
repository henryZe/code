#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <linux/ioctl.h>
#include <mach/irqs.h>
#include <linux/platform_device.h>


static struct resource bast_dm9k_resource[] = {
	[0] = {
		.start = 0x88000000,
		.end   = 0x88000000 + 3,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = 0x88000000 + 0x4,
		.end   = 0x88000000 + 0x4 + 3,
		.flags = IORESOURCE_MEM,
	},
	[2] = {
		.start = IRQ_EINT(7),
		.end   = IRQ_EINT(7),
		.flags = IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHLEVEL,
	}
};

static struct platform_device bast_device_dm9k = {
	.name		= "dm9000",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(bast_dm9k_resource),
	.resource	= bast_dm9k_resource,
};


static int __init net_dev_init(void)
{
	int ret1;

	ret1 = platform_device_register(&bast_device_dm9k);
	if(ret1)
	{
		goto err1;
	}

	return 0;

err1:
	printk(KERN_ERR "platform net device register failed!\n");
	return ret1;
}


static void __exit net_dev_exit(void)
{
	platform_device_unregister(&bast_device_dm9k);

}


module_init(net_dev_init);
module_exit(net_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("henry_Z");
MODULE_DESCRIPTION("net driver");
MODULE_SUPPORTED_DEVICE("DM9000");
