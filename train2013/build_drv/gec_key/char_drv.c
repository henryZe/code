#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#include <linux/platform_device.h>

#include <linux/ioport.h>
#include <asm/io.h>

#include <linux/interrupt.h>
#include <plat/irqs.h>

#include <linux/input.h>

#include <mach/gpio.h>


struct input_dev *gec_key;
struct resource *key_res[8];

int key_num[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };


static irqreturn_t handler_entry(int irq, void *data)
{
	switch(*(int *)data)
	{
		case 0:
			input_report_key(gec_key, KEY_A, !gpio_get_value(S5PV210_GPH2(0)));
			input_sync(gec_key);
			break;
		case 1:	
			input_report_key(gec_key, KEY_B, !gpio_get_value(S5PV210_GPH2(1)));
			input_sync(gec_key);
			break;
		case 2:
			input_report_key(gec_key, KEY_C, !gpio_get_value(S5PV210_GPH2(2)));
			input_sync(gec_key);	
			break;
		case 3:
			input_report_key(gec_key, KEY_D, !gpio_get_value(S5PV210_GPH2(3)));
			input_sync(gec_key);
			break;
		case 4:
			input_report_key(gec_key, KEY_E, !gpio_get_value(S5PV210_GPH3(0)));
			input_sync(gec_key);
			break;
		case 5:
			input_report_key(gec_key, KEY_F, !gpio_get_value(S5PV210_GPH3(1)));
			input_sync(gec_key);
			break;
		case 6:
			input_report_key(gec_key, KEY_G, !gpio_get_value(S5PV210_GPH3(2)));
			input_sync(gec_key);
			break;
		case 7:
			input_report_key(gec_key, KEY_H, !gpio_get_value(S5PV210_GPH3(3)));
			input_sync(gec_key);
			break;
	}	

	return IRQ_HANDLED;
}

static int gec_key_probe(struct platform_device *pdev)
{
	int ret, i;
	
	//分配空间
	gec_key = input_allocate_device();
	if(!gec_key)
	{
		goto input_allocate_device_err;
	}


	//填充结构体
	gec_key->evbit[0] = BIT_MASK(EV_KEY)|BIT_MASK(EV_ABS);
	
	gec_key->keybit[BIT_WORD(KEY_A)] = BIT_MASK(KEY_A);
	gec_key->keybit[BIT_WORD(KEY_B)] |= BIT_MASK(KEY_B);
	gec_key->keybit[BIT_WORD(KEY_C)] |= BIT_MASK(KEY_C);
	gec_key->keybit[BIT_WORD(KEY_D)] |= BIT_MASK(KEY_D);
	gec_key->keybit[BIT_WORD(KEY_E)] |= BIT_MASK(KEY_E);
	gec_key->keybit[BIT_WORD(KEY_F)] |= BIT_MASK(KEY_F);
	gec_key->keybit[BIT_WORD(KEY_G)] |= BIT_MASK(KEY_G);
	gec_key->keybit[BIT_WORD(KEY_H)] |= BIT_MASK(KEY_H);

	//input_dev,type,0~4095(12bits),20波动值
	input_set_abs_params(gec_key, ABS_X, 0, 4095, 20, 0);
	input_set_abs_params(gec_key, ABS_Y, 0, 4095, 20, 0);
	input_set_abs_params(gec_key, ABS_Z, 0, 4095, 20, 0);
	input_set_abs_params(gec_key, ABS_PRESSURE, 0, 1, 0, 0);

	//产品信息
	gec_key->name = "whole_key";
	gec_key->id.bustype = 0x12;
	gec_key->id.vendor  = 0x34;
	gec_key->id.version = 0x56;
	gec_key->id.product = 0x78;
	

	//注册结构体
	ret = input_register_device(gec_key);
	if(ret)
	{
		goto input_register_device_err;
	}

	
	//与硬件交联
	for(i=0; i<8; i++)
	{
		key_res[i] = platform_get_resource(pdev, IORESOURCE_IRQ, key_num[i]);
		if(!key_res[i])
		{
			goto platform_get_resource_err;
		}

		ret = request_irq(key_res[i]->start, handler_entry, IRQF_DISABLED|IRQF_TRIGGER_RISING|IRQF_TRIGGER_FALLING, key_res[i]->name, &key_num[i]);
		if(ret)
		{
			goto request_irq_err;
		}
	}
	printk("probe success!\n");

	return 0;

input_allocate_device_err:
	printk(KERN_ERR "allocate input device failed!\n");
	return -EFAULT;
input_register_device_err:
	printk(KERN_ERR "register device failed!\n");
	input_free_device(gec_key);
	return -EFAULT;

platform_get_resource_err:
	printk(KERN_ERR "platform get resource failed!\n");
	return -EFAULT;	
request_irq_err:
	printk(KERN_ERR "request irq failed!\n");
	for(i=i-1; i>=0; i--)
	{
		free_irq(key_res[i]->start, NULL);
	}
	return -EFAULT;		
}

static int gec_key_remove(struct platform_device *pdev)
{
	int i;

	input_unregister_device(gec_key);
	
	for(i=0; i<8; i++)
	{
		free_irq(key_res[i]->start, &key_num[i]);
	}
	printk("key_drv remove\n");

	return 0;
}

struct platform_driver gec_key_drv = 
{
	.probe  = gec_key_probe,
	.remove = gec_key_remove,
	.driver = 
	{
		.name = "gec_dev",
	},
	
};

static int __init gec_drv_init(void)
{
	int error;

	error = platform_driver_register(&gec_key_drv);
	if(error)
	{
		goto platform_driver_register_err;
	}
	
	printk(KERN_ALERT "platform driver register OK!\n");

	return 0;


platform_driver_register_err:
	printk(KERN_ERR "platform driver register failed!\n");
	return -EFAULT;	
}

static void __exit gec_drv_exit(void)
{
	platform_driver_unregister(&gec_key_drv);
}


module_init(gec_drv_init);
module_exit(gec_drv_exit);

MODULE_AUTHOR("henry_Z");
MODULE_DESCRIPTION("char drivers");
MODULE_VERSION("v0.1");
MODULE_LICENSE("GPL");
