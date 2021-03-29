#include <linux/module.h>		
#include <linux/init.h>	
#include <linux/fs.h>

#include <linux/kernel.h>
#include <linux/moduleparam.h>

#include "sub.h"


/*
args sub_arg;
module_param(sub_arg.st,int,0);
module_param(sub_arg.nd,int,0);
module_param(sub_arg.result,int,0);
*/

int a=0;
int b=0;
module_param(a,int,0);
module_param(b,int,0);

int x=0;
int y=0;
module_param(x,int,0);
module_param(y,int,0);

int add(int arg1,int arg2);

static int __init drv_init(void)
{	
/*	sub_arg.result = sub(sub_arg.st,sub_arg.nd);

	printk(KERN_INFO "a = %d\n",sub_arg.st);
	printk(KERN_INFO "b = %d\n",sub_arg.nd);
	printk(KERN_INFO "a-b = %d\n",sub_arg.result);
*/
	
	printk(KERN_INFO "a-b = %d\n",sub(a,b));
	printk(KERN_INFO "x+y = %d\n",add(x,y));
	return 0;
}

static void __exit drv_exit(void)
{
	printk(KERN_WARNING "drv exit\n");
}

module_init(drv_init);
module_exit(drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("henry_Z");
MODULE_DESCRIPTION("my first drive for fun");
