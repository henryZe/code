#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <linux/ioctl.h>
#include <mach/irqs.h>
#include <linux/platform_device.h>
#include "lcd_dev.h"


static struct resource lcd_resource[] = 
{
	[0] = {
		.start = GPF0CON,
		.end   = GPF0CON+ 3,
		.flags = IORESOURCE_MEM,
		.name = "GPF0CON",
	},
	[1] = {
		.start = GPF1CON,
		.end   = GPF1CON+ 3,
		.flags = IORESOURCE_MEM,
		.name = "GPF1CON",
	},
	[2] = {
		.start = GPF2CON,
		.end   = GPF2CON+ 3,
		.flags = IORESOURCE_MEM,
		.name = "GPF2CON",
	},
	[3] = {
		.start = GPF3CON,
		.end   = GPF3CON+ 3,
		.flags = IORESOURCE_MEM,
		.name = "GPF3CON",
	},
	[4] = {
		.start = SRC_MASK,
		.end   = SRC_MASK+ 3,
		.flags = IORESOURCE_MEM,
		.name = "SRC_MASK",
	},
	[5] = {
		.start = CLK_GATE,
		.end   = CLK_GATE+ 3,
		.flags = IORESOURCE_MEM,
		.name = "CLK_GATE",
	},
	[6] = {
		.start = CLK_SRC1,
		.end   = CLK_SRC1+ 3,
		.flags = IORESOURCE_MEM,
		.name = "CLK_SRC1",
	},
	[7] = {
		.start = CLK_DIV1,
		.end   = CLK_DIV1+ 3,
		.flags = IORESOURCE_MEM,
		.name = "CLK_DIV1",
	},
	[8] = {
		.start = DCONTROL,
		.end   = DCONTROL+ 3,
		.flags = IORESOURCE_MEM,
		.name = "DCONTROL",
	},
	[9] = {
		.start = VIDCON0,
		.end   = VIDCON0+ 3,
		.flags = IORESOURCE_MEM,
		.name = "VIDCON0",
	},
	[10] = {
		.start = VIDCON1,
		.end   = VIDCON1+ 3,
		.flags = IORESOURCE_MEM,
		.name = "VIDCON1",
	},
	[11] = {
		.start = VIDCON2,
		.end   = VIDCON2+ 3,
		.flags = IORESOURCE_MEM,
		.name = "VIDCON2",
	},
	[12] = {
		.start = VIDTCON0,
		.end   = VIDTCON0+ 3,
		.flags = IORESOURCE_MEM,
		.name = "VIDTCON0",
	},
	[13] = {
		.start = VIDTCON1,
		.end   = VIDTCON1+ 3,
		.flags = IORESOURCE_MEM,
		.name = "VIDTCON1",
	},
	[14] = {
		.start = VIDTCON2,
		.end   = VIDTCON2+3,
		.flags = IORESOURCE_MEM,
		.name = "VIDTCON2",
	},

	[15] = {
		.start = WINCON0,
		.end   = WINCON0+ 3,
		.flags = IORESOURCE_MEM,
		.name = "WINCON0",
	},
	[16] = {
		.start = WINCON2,
		.end   = WINCON2+ 3,
		.flags = IORESOURCE_MEM,
		.name = "WINCON2",
	},
	[17] = {
		.start = SHADOWCON,
		.end   = SHADOWCON+ 3,
		.flags = IORESOURCE_MEM,
		.name = "SHADOWCON",
	},
	[18] = {
		.start = VIDOSD0A,
		.end   = VIDOSD0A+ 3,
		.flags = IORESOURCE_MEM,
		.name = "VIDOSD0A",
	},
	[19] = {
		.start = VIDOSD0B,
		.end   = VIDOSD0B+ 3,
		.flags = IORESOURCE_MEM,
		.name = "VIDOSD0B",
	},
	[20] = {
		.start = VIDOSD0C,
		.end   = VIDOSD0C+3,
		.flags = IORESOURCE_MEM,
		.name = "VIDOSD0C",
	},
	[21] = {
		.start = VIDW00ADD0B0,
		.end   = VIDW00ADD0B0+ 3,
		.flags = IORESOURCE_MEM,
		.name = "VIDW00ADD0B0",
	},
	[22] = {
		.start = VIDW00ADD1B0,
		.end   = VIDW00ADD1B0+ 3,
		.flags = IORESOURCE_MEM,
		.name = "VIDW00ADD1B0",
	},
	[23] = {
		.start = VIDW00ADD2,
		.end   = VIDW00ADD2+ 3,
		.flags = IORESOURCE_MEM,
		.name = "VIDW00ADD2",
	},
	[24] = {
		.start = GPJ2CON,
		.end   = GPJ2CON+ 3,
		.flags = IORESOURCE_MEM,
		.name = "GPJ2CON",
	},
	[25] = {
		.start = GPJ2PUD,
		.end   = GPJ2PUD+ 3,
		.flags = IORESOURCE_MEM,
		.name = "GPJ2PUD",
	},
	[26] = {
		.start = GPJ2DAT,
		.end   = GPJ2DAT+ 3,
		.flags = IORESOURCE_MEM,
		.name = "GPJ2DAT",
	},
	[27] = {
		.start = CLK_GATE_BLOCK,
		.end   = CLK_GATE_BLOCK+ 3,
		.flags = IORESOURCE_MEM,
		.name = "CLK_GATE_BLOCK",
	},
};


void lcd_release(struct device *dev)
{
	printk(KERN_ALERT "lcd device release!\n");
}


static struct platform_device lcd_dev =
{
	.name		= "gec_lcd",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(lcd_resource),
	.resource	= lcd_resource,
	.dev =
	{
		.release = lcd_release,
	},
};


static int __init lcd_dev_init(void)
{
	int ret1;
	ret1 = platform_device_register(&lcd_dev);
	if(ret1)
	{
		goto err1;
	}

	return 0;

err1:
	printk(KERN_ERR "platform device register failed!\n");
	return ret1;
}

static void __exit lcd_dev_exit(void)
{
	platform_device_unregister(&lcd_dev);
}


module_init(lcd_dev_init);
module_exit(lcd_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("henry_Z");
MODULE_DESCRIPTION("lcd driver");
