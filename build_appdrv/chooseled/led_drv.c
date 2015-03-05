#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/delay.h>

#include <mach/gpio.h>
#include <mach/regs-gpio.h>
#include <plat/gpio-cfg.h>


#define DEVICE_NAME "leds"

static int led_gpios[] = {
	S5PV210_GPJ2(0),
	S5PV210_GPJ2(1),
	S5PV210_GPJ2(2),
	S5PV210_GPJ2(3),
};

#define LED_NUM		ARRAY_SIZE(led_gpios)

#define LED_MAGIC 'x'   //设置魔数
#define LED1 _IO(LED_MAGIC,0)
#define LED2 _IO(LED_MAGIC,1)
#define LED3 _IO(LED_MAGIC,2)
#define LED4 _IO(LED_MAGIC,3)
#define MAX_NR 4

static long gec210_leds_ioctl(struct file *filp, unsigned int cmd,
		unsigned long arg)
{
	printk("_IOC_NR(cmd)=%d arg=%d\n",_IOC_NR(cmd),(int)arg);

        if( _IOC_TYPE(cmd) != LED_MAGIC )
            return -EINVAL;
        if( _IOC_NR(cmd) > MAX_NR ) 
            return -EINVAL;
	switch( cmd ) {

		case LED1:  //设置LED1 的开或者关
			gpio_set_value(led_gpios[_IOC_NR(cmd)],arg);
			printk("led 1\n");
			break;

		case LED2:  //设置LED2 的开或者关
			gpio_set_value(led_gpios[_IOC_NR(cmd)],arg);
			printk("led2\n");
			break;

		case LED3:  //设置LED3 的开或者关
			gpio_set_value(led_gpios[_IOC_NR(cmd)],arg);
			printk("led3\n");
			break;

		case LED4:  //设置LED4 的开或者关
			gpio_set_value(led_gpios[_IOC_NR(cmd)],arg);
			printk("led4\n");
			break;

		default:

			printk("default\n");

			return -EINVAL;

	}
	return 0;
}

static struct file_operations gec210_led_dev_fops = {
	.owner			= THIS_MODULE,
	.unlocked_ioctl	= gec210_leds_ioctl,
};

static struct miscdevice gec210_led_dev = {
	.minor			= MISC_DYNAMIC_MINOR,
	.name			= DEVICE_NAME,
	.fops			= &gec210_led_dev_fops,
};

static int __init gec210_led_dev_init(void) {
	int ret;
	int i;

	for (i = 0; i < LED_NUM; i++) {
		ret = gpio_request(led_gpios[i], "LED");
		if (ret) {
			printk("%s: request GPIO %d for LED failed, ret = %d\n", DEVICE_NAME,
					led_gpios[i], ret);
			return ret;
		}

		s3c_gpio_cfgpin(led_gpios[i], S3C_GPIO_OUTPUT);
		gpio_set_value(led_gpios[i], 1);
	}

	ret = misc_register(&gec210_led_dev);

	printk(DEVICE_NAME"\tinitialized\n");

	return ret;
}

static void __exit gec210_led_dev_exit(void) {
	int i;

	for (i = 0; i < LED_NUM; i++) {
		gpio_free(led_gpios[i]);
	}

	misc_deregister(&gec210_led_dev);
}

module_init(gec210_led_dev_init);
module_exit(gec210_led_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("GEC Inc.");