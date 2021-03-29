#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/sched.h>

#include "second_device.h"

static int second_major;
module_param(second_major, int, S_IRUGO);

struct second_dev {
	struct cdev cdev;
	atomic_t counter;
	struct timer_list s_timer;
};

static struct second_dev *second_devp;

static void second_timer_handler(unsigned long data)
{
	struct second_dev *dev = (struct second_dev *)data;

	mod_timer(&dev->s_timer, jiffies + HZ);
	atomic_inc(&dev->counter);

	printk("current jiffies is %ld\n", jiffies);
}

static int second_open(struct inode *inode, struct file *filp)
{
	init_timer(&second_devp->s_timer);
	second_devp->s_timer.function = &second_timer_handler;
	second_devp->s_timer.data = (unsigned long)second_devp;

	/* jiffies + 1s */
	second_devp->s_timer.expires = jiffies + HZ;

	add_timer(&second_devp->s_timer);

	atomic_set(&second_devp->counter, 0);

	return 0;
}

static int second_release(struct inode *inode, struct file *filp)
{
	del_timer(&second_devp->s_timer);

	return 0;
}

static ssize_t second_read(struct file *filp, char __user *buf, size_t size, loff_t *pos)
{
	int ret, counter;

	counter = atomic_read(&second_devp->counter);

	ret = copy_to_user((void *)buf, &counter, sizeof(counter));
	if (ret)
		return -EFAULT;

	return ret;
}

static const struct file_operations second_fops = {
	.owner = THIS_MODULE,
	.open = second_open,
	.release = second_release,
	.read = second_read,
};

static void second_setup_cdev(struct second_dev *dev, int index)
{
	int err, devno = MKDEV(second_major, 0);

	cdev_init(&dev->cdev, &second_fops);
	dev->cdev.owner = THIS_MODULE;
	err = cdev_add(&dev->cdev, devno, 1);
	if (err)
		printk("failed to add second device\n");
}

static int __init second_init(void)
{
	int ret;
	dev_t devno = MKDEV(second_major, 0);

	if (second_major) {
		printk("register globalfifo major: %d\n", second_major);
		ret = register_chrdev_region(devno, 1, DEV_NAME);
	} else {
		ret = alloc_chrdev_region(&devno, 0, 1, DEV_NAME);
		second_major = MAJOR(devno);
		printk("allocate globalfifo major: %d\n", second_major);
	}

	if (ret < 0)
		return ret;

	second_devp = kzalloc(sizeof(struct second_dev), GFP_KERNEL);
	if (!second_devp) {
		ret = -ENOMEM;
		goto fail_malloc;
	}

	second_setup_cdev(second_devp, 0);

	printk("second_init\n");
	return 0;

fail_malloc:
	unregister_chrdev_region(devno, 1);
	return ret;
}
module_init(second_init);

static void __exit second_exit(void)
{
	cdev_del(&second_devp->cdev);

	kfree(second_devp);

	unregister_chrdev_region(MKDEV(second_major, 0), 1);

	printk("second_exit\n");
}
module_exit(second_exit);

MODULE_AUTHOR("Henry.Zeng");
MODULE_DESCRIPTION("second device");
MODULE_LICENSE("GPL v2");
MODULE_VERSION("1.0.0");
