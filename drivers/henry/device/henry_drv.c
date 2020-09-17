#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/slab.h>

static char *test_charp = "default content";
module_param(test_charp, charp, S_IRUGO | S_IWUSR);
static int test_int = 0;
module_param(test_int, int, S_IRUGO | S_IWUSR);
static int fish[3];
static int nr_fish = 3;
module_param_array(fish, int, &nr_fish, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(fish, "fish pounds");

static int __init henry_init(void)
{
	printk("%s\n", test_charp);
	printk("int:%d\n", test_int);
	printk("henry_init\n");
	
	return 0;
}
module_init(henry_init);

static void __exit henry_exit(void)
{
	printk("henry_exit\n");
}
module_exit(henry_exit);

MODULE_AUTHOR("Henry.Zeng");
MODULE_DESCRIPTION("HENRY Driver for test");
MODULE_LICENSE("GPL v2");
MODULE_VERSION("1.2.0");
