#include <linux/module.h>		
#include <linux/init.h>	
#include <linux/fs.h>

#include <linux/kernel.h>
#include <linux/moduleparam.h>


static int add(int x, int y)
{			
	return x+y;
}

static int __init drv_init(void)
{
	printk(KERN_WARNING "add init\n");
	return 0;
}

static void __exit drv_exit(void)
{
	printk(KERN_WARNING "add exit\n");
}

module_init(drv_init);
module_exit(drv_exit);

EXPORT_SYMBOL(add);

MODULE_LICENSE("GPL");
