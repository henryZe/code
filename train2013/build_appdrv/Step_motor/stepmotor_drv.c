#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <linux/delay.h>
#include <linux/poll.h>
#include <linux/spinlock.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/cdev.h>

#include <mach/hardware.h>
#include <asm/io.h>
#include <mach/regs-gpio.h>
#include <plat/regs-timer.h>
#include <mach/gpio.h>
#include "common.h"


struct class *gec_class;
struct mydev_t {
	int major,minor;
	dev_t dev_num;
	
	struct cdev my_cdev;
};

struct mydev_t chardev;

#define   MOTOA     S5PV210_GPH0(4)
#define   MOTOB     S5PV210_GPH1(1)
#define   MOTOC     S5PV210_GPH0(3)
#define   MOTOD     S5PV210_GPH0(5)

#define   GPIOSET(PIN)  gpio_direction_output(PIN,1)
#define   GPIOCLR(PIN)  gpio_direction_output(PIN,0)

static int flag=0;
static unsigned int new_value;

static int ready = 0;
static DECLARE_WAIT_QUEUE_HEAD(timer_wait);//生成一个等待队列timer_wait

/*********************************************************************************************************
** Function name: MOTO_Mode2
** Descriptions : 步进电机八拍运行, 时序为AB--BC--CD--DA--AB, 转20*4步
**                步距角为18度,即,转动80*18度=4*360度,转动4圈
** Input : dly, 每一步时延,即步进速度.
********************************************************************************************************/
static void motor_anti_clockwise(void)
{
   	int i;

    for(i=0; i<40; i++) 
	{
       	ready=0;
		// AD
		GPIOSET(MOTOA);
		GPIOSET(MOTOD);

       	//DelayNS1(dly);
       	wait_event_interruptible(timer_wait, ready == 1);
		ready=0;
		
		// A
       	GPIOCLR(MOTOD);
		wait_event_interruptible(timer_wait, ready == 1);
		ready=0;
		
		//BA
		GPIOSET(MOTOB);
		GPIOSET(MOTOA);

       	//DelayNS1(dly);
       	wait_event_interruptible(timer_wait, ready == 1);
		ready=0;
		
		// B
		GPIOCLR(MOTOA);
		wait_event_interruptible(timer_wait, ready == 1);
		ready=0;

		//CB
		GPIOSET(MOTOC);
		GPIOSET(MOTOB);

       	//DelayNS1(dly);
       	wait_event_interruptible(timer_wait, ready == 1);
		ready=0;
		
       	// C
		GPIOCLR(MOTOB);
		wait_event_interruptible(timer_wait, ready == 1);
		ready=0;
		
		//DC
		GPIOSET(MOTOD);
		GPIOSET(MOTOC);

       	//DelayNS1(dly);
       	wait_event_interruptible(timer_wait, ready == 1);
		ready=0;
		
       	// D
		GPIOCLR(MOTOC);
		wait_event_interruptible(timer_wait, ready == 1);
		ready=0;
    	}
        GPIOCLR(MOTOD);
}

void motor_clockwise(void)
{
   	int i;

   	for(i=0; i<40; i++)
    {
		ready=0;
        // DA
        GPIOSET(MOTOD);
        GPIOSET(MOTOA);
        //DelayNS(dly);
      	wait_event_interruptible(timer_wait, ready == 1);
		ready=0;
        	
		// D
		GPIOCLR(MOTOA);
		wait_event_interruptible(timer_wait, ready == 1);
		ready=0;
		

        // CD
        GPIOSET(MOTOC);
        GPIOSET(MOTOD);
        //DelayNS(dly);
     	wait_event_interruptible(timer_wait, ready == 1);
		ready=0;
		
        // C
		GPIOCLR(MOTOD);
		wait_event_interruptible(timer_wait, ready == 1);
		ready=0;

        // BC
        GPIOSET(MOTOB);
        GPIOSET(MOTOC);
        //DelayNS(dly);
     	wait_event_interruptible(timer_wait, ready == 1);
		ready=0;
		
        // B
		GPIOCLR(MOTOC);
		wait_event_interruptible(timer_wait, ready == 1);
		ready=0;
        	
		// AB
        GPIOSET(MOTOA);
        GPIOSET(MOTOB);
        //DelayNS(dly);
     	wait_event_interruptible(timer_wait, ready == 1);
		ready=0;
		
        // A
		GPIOCLR(MOTOB);
		wait_event_interruptible(timer_wait, ready == 1);
		ready=0;
    }
		GPIOCLR(MOTOA);
}

static void motor_speedup(void)
{
	flag=1;
	if(new_value > 100)
		new_value -=100;
	else
		printk("can not speed it anymore!");
	printk("value_now=%d\n",new_value);
}

static void motor_speeddown(void)
{
	flag=1;
	if(new_value <1200) {
		new_value +=100;
	}
	else
		printk("can not slow it anymore!");
	printk("value_now=%d\n",new_value);
}

/*************************************************************************
*  * Timer input clock Frequency = PCLK / {prescaler value+1} / {divider value}
*  * {prescaler value} = 0~255
*  * {divider value} = 2, 4, 8, 16
*  * 本实验的Timer2的时钟频率=50MHz/(225+1)/(16)=12207Hz,中断时间为0.1秒
*  * 设置Timer2 没隔0.2秒钟触发一次中断：
*************************************************************************/
void Timer2_init(void)
{
	__raw_writel(__raw_readl(S3C2410_TCFG0) | (128<<8), S3C2410_TCFG0);
	__raw_writel(__raw_readl(S3C2410_TCFG1) | (0x03<<8), S3C2410_TCFG1);
	__raw_writel(new_value, S3C2410_TCNTB(2));//value---1220:0.1s    
	__raw_writel((__raw_readl(S3C2410_TCON) & (~(0x0f<<12))) | (0x0b<<12), 
		S3C2410_TCON);//atuo reload, Timer 2 manual update, Timer 2 start
	__raw_writel(__raw_readl(S3C2410_TCON) & (~(2<<12)), S3C2410_TCON);	
}

//--------------------------------------------
static irqreturn_t timer2_irq_handle(int irq, void *devid)
{
	ready=1;
	wake_up_interruptible(&timer_wait);		//wake up

	if(flag !=0) {
	flag = 0;
	   __raw_writel(new_value, S3C2410_TCNTB(2));//value   
	   __raw_writel((__raw_readl(S3C2410_TCON)&(~(0x0f<<12)))|(0x0b<<12)
	   		,S3C2410_TCON); 
			//atuo reload, Timer 0 manual update, Timer 0 start
	   __raw_writel(__raw_readl(S3C2410_TCON)&(~(2<<12)),S3C2410_TCON);
	}
	return IRQ_HANDLED;
}

static int s3c2410_motor_open(struct inode *inode, struct file *filp)
{
	int ret;

	printk("step_drv_open\n");
	
	gpio_request(S5PV210_GPH0(4),"MOTOA");
	gpio_request(S5PV210_GPH1(1),"MOTOB");
	gpio_request(S5PV210_GPH0(3),"MOTOC");
	gpio_request(S5PV210_GPH0(5),"MOTOD");


	s3c_gpio_cfgpin(S5PV210_GPH0(3), 1);
	s3c_gpio_cfgpin(S5PV210_GPH0(4), 1);
	s3c_gpio_cfgpin(S5PV210_GPH0(5), 1);
	s3c_gpio_cfgpin(S5PV210_GPH1(1), 1);

	ret = request_irq(IRQ_TIMER2, timer2_irq_handle, IRQF_DISABLED,//logic timer2 interrupt 
				"TIMER2", NULL);	
	if(ret)
		goto request_irq_err;

	new_value=600;
	ready=0;
	
	Timer2_init();		//init Timer2 and start
	
	return 0;
	
request_irq_err:
	printk( " Failed to request timer2.\n");
	return -EFAULT;
}

static int s3c2410_motor_ioctl(struct inode *inode, struct file *file,
		     unsigned int cmd, unsigned long arg)
{

	if (arg > 1) {
		printk("arg is wrong!\n");
		return -EINVAL;
	}

	if(_IOC_TYPE(cmd) != WON_MAGIC)
	{
		printk("your magic number is error\n");
		return -1;
	}
	
	switch(_IOC_NR(cmd)) {
		case 1:		//clockwise
			printk("clockwise\n");
			motor_clockwise();
			break;
		case 2:	//anti_clockwise
			printk("anti_clockwise\n");
			motor_anti_clockwise();
			break;
		case 3:	//speedup
			motor_speedup();
			printk("speedup\n");
			break;
		case 4:	//speeddown
			motor_speeddown();
			printk("speeddown\n");
			break;
		default:
			return -EINVAL;
	}	
	return 0;
}

static int s3c2410_motor_release(struct inode *inode, struct file *filp)
{
	printk("step_drv_release\n");

	new_value=600;
	ready=0;
	__raw_writel(__raw_readl(S3C2410_TCON) & (~(0x0f<<12)), S3C2410_TCON);//close timer2
	free_irq(IRQ_TIMER2, NULL);
	
	return 0;
}

ssize_t s3c2410_motor_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
	unsigned long read;

	printk("step_drv_read\n");
	
	read = copy_to_user((void *)buf, &new_value, count);
	if(read)
	{
		printk("read fail\n");
		return -1;
	}

	return 0;
}

static struct file_operations s3c2410_fops = {
	owner:	THIS_MODULE,
	open:	s3c2410_motor_open,
	read:   s3c2410_motor_read,
	ioctl:	s3c2410_motor_ioctl,
	release:	s3c2410_motor_release,
};

static int __init  motor_driver_init(void)
{
	int err;

	printk("s3c2410  motor_driver init\n");

	chardev.major = 0;
	chardev.minor = 0;
	chardev.dev_num = MKDEV(chardev.major,chardev.minor);

	err = alloc_chrdev_region(&chardev.dev_num, 0, 1, "Step_num");

	if(err)
	{
		printk("char device region fail\n");
		return -1;
	}

	cdev_init(&chardev.my_cdev, &s3c2410_fops);
	cdev_add(&chardev.my_cdev, chardev.dev_num, 1);

	printk("char device region success\n");
	
	gec_class = class_create(THIS_MODULE, "gec_smotors");
	if(!gec_class)
	{
		printk("class_create err\n");
		return -EFAULT;
	}

	//class, *parent, dev_t, *drvdata, const char *fmt
	device_create(gec_class, NULL, chardev.dev_num, NULL, "gec_smotor");
	printk("make device node success\n");
	
	Timer2_init();		//init Timer2 and start
	return err;
}


static void __exit  motor_driver_exit(void)
{
	printk(" motor_driver_exit!\n");
	gpio_free(MOTOA);
	gpio_free(MOTOB);
	gpio_free(MOTOC);
	gpio_free(MOTOD);
	
	cdev_del(&chardev.my_cdev);
	unregister_chrdev_region(chardev.dev_num, 1);
} 

module_init( motor_driver_init);
module_exit( motor_driver_exit);

MODULE_DESCRIPTION("STEP MOTOR driver");
MODULE_LICENSE("GPL");
