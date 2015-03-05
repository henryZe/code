#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/input.h>
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/serio.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <linux/miscdevice.h>


#include <asm/io.h>
#include <asm/irq.h>
#include <asm/uaccess.h>
#include <mach/regs-adc.h>
#include <mach/regs-gpio.h>
#include <plat/gpio-cfg.h>
#include <mach/gpio.h>

#define DEVICE_NAME "humidity"

//XEINT24/KP_ROW0/GPH3_0
unsigned long receive_value;
unsigned long receive_jy;

int data_in(void)
{
	s3c_gpio_cfgpin(S5PV210_GPH3(0), S3C_GPIO_INPUT);
	return gpio_get_value(S5PV210_GPH3(0));
}


void data_out(int data)
{
	s3c_gpio_cfgpin(S5PV210_GPH3(0), S3C_GPIO_OUTPUT);
	gpio_set_value(S5PV210_GPH3(0), data); 
}

void read_data(void)
{
	unsigned int flag = 0;
	unsigned int u32i = 0;
	
	data_out(0);
	mdelay(20);
	data_out(1);
	udelay(40);
	if (data_in() == 0)
	{
		while( (data_in() == 0) && ((flag++)<50000) );
		flag = 0;
		receive_value = 0;
		receive_jy = 0;
		while( data_in() != 0 );
		for (u32i=0x80000000; u32i>0; u32i>>=1)
		{
			flag = 0;
			while( (data_in() == 0) && ((flag++)<50000) );
			flag = 0;
			while( (data_in() != 0) && ((flag)<500))
			{
				udelay(10);
				flag++;
			}
			
			if(flag > 5)
			{
	//			printk("flag 1= %d\n",flag);
				receive_value |= u32i;
			}
		}
	//			printk("flag 0= %d\n",flag);
		for (u32i=0x80; u32i>0; u32i>>=1)
		{
			flag = 0;
			while( (data_in() == 0) && ((flag++)<50000) );
			flag = 0;
			while( (data_in() != 0) && ((flag)<500))
			{
				udelay(10);
				flag++;
			}
			
			if(flag > 5)
			{
				receive_jy |= u32i;
			}
		}
	}
}

static ssize_t gec210_humidiy_read(struct file *file, char __user *buf, size_t size, loff_t *off)
{
//	unsigned short tempz = 0;
//	unsigned short tempx = 0;
//	unsigned short humidiyz = 0;
//	unsigned short humidiyx = 0;

	read_data();
//	humidiyz = (receive_value & 0xff000000)>>24;
//	humidiyx = (receive_value & 0x00ff0000)>>16;
//	tempz = (receive_value & 0x0000ff00)>>8;
//	tempx = (receive_value & 0x000000ff);
	copy_to_user(buf,&receive_value,sizeof (receive_value));
	return 0;
}

static int gec210_humidiy_open(struct inode *inode, struct file *file)
{
	printk("open in kernel\n");
	return 0;
}

static void gec210_humidiy_release(struct inode *inode, struct file *file)
{
	printk("the dev is close\n");
}

static struct file_operations gec210_humidity_dev_fops = {
	.owner			= THIS_MODULE,
	.open = gec210_humidiy_open,
	.read = gec210_humidiy_read,
	.release = gec210_humidiy_release
};

static struct miscdevice gec210_humidity_dev = {
	.minor			= MISC_DYNAMIC_MINOR,
	.name			= DEVICE_NAME,
	.fops			= &gec210_humidity_dev_fops,
};

static int __init gec210_humidity_dev_init(void) {
	int ret;
	ret = gpio_request(S5PV210_GPH3(0), "humidity");
		if (ret) {
			printk("%s: request GPIO %d for humidity failed, ret = %d\n", DEVICE_NAME,
					S5PV210_GPH3(0), ret);
			return ret;
		}

		s3c_gpio_cfgpin(S5PV210_GPH3(0), 1);
		gpio_set_value(S5PV210_GPH3(0), 1);
	

	ret = misc_register(&gec210_humidity_dev);

	printk(DEVICE_NAME"\tinitialized\n");
	return ret;
}

static void __exit gec210_humidity_dev_exit(void)
{
	gpio_free(S5PV210_GPH3(0));
	misc_deregister(&gec210_humidity_dev);
}

module_init(gec210_humidity_dev_init);
module_exit(gec210_humidity_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Gec Lab.");


