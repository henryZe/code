#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/cdev.h>

#include "global_mem.h"

static int globalmem_major;
module_param(globalmem_major, int, S_IRUGO);

struct globalmem_dev {
	struct cdev cdev;
	unsigned char mem[GLOBALMEM_SIZE];
	struct mutex mutex;
};

struct globalmem_dev *globalmem_devp;

static loff_t globalmem_llseek(struct file *filp, loff_t offset, int orig)
{
	loff_t ret = 0;

	switch (orig) {

	/* file pos beginning */
	case SEEK_SET:
		if (offset < 0) {
			ret = -EINVAL;
			break;
		}

		if ((unsigned int)offset > GLOBALMEM_SIZE) {
			ret = -EINVAL;
			break;
		}

		filp->f_pos = (unsigned int)offset;
		ret = filp->f_pos;
		break;

	/* file pos current */
	case SEEK_CUR:
		if ((filp->f_pos + offset) > GLOBALMEM_SIZE) {
			ret = -EINVAL;
			break;
		}

		if ((filp->f_pos + offset) < 0) {
			ret = -EINVAL;
			break;
		}

		filp->f_pos += offset;
		ret = filp->f_pos;
		break;

	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}

static ssize_t globalmem_read(struct file *filp,
	char __user *buf, size_t size, loff_t *ppos)
{
	int ret = 0;
	unsigned int count = size;
	struct globalmem_dev *dev = filp->private_data;

	if (*ppos >= GLOBALMEM_SIZE)
		return 0;

	if (count > GLOBALMEM_SIZE - *ppos)
		count = GLOBALMEM_SIZE - *ppos;

	mutex_lock(&dev->mutex);

	if (copy_to_user(buf, dev->mem + *ppos, count))
		ret = -EFAULT;
	else {
		printk("read %u byte(s) from %llu\n", count, *ppos);

		*ppos += count;
		ret = count;
	}

	mutex_unlock(&dev->mutex);

	return ret;
}

static ssize_t globalmem_write(struct file *filp,
	const char __user *buf, size_t size, loff_t *ppos)
{
	int ret = 0;
	unsigned int count = size;
	struct globalmem_dev *dev = filp->private_data;

	if (*ppos >= GLOBALMEM_SIZE)
		return 0;

	if (count > GLOBALMEM_SIZE - *ppos)
		count = GLOBALMEM_SIZE - *ppos;

	mutex_lock(&dev->mutex);

	if (copy_from_user(dev->mem + *ppos, buf, count))
		return -EFAULT;
	else {
		printk("write %u byte(s) to %llu\n", count, *ppos);

		*ppos += count;
		ret = count;
	}

	mutex_unlock(&dev->mutex);

	return ret;
}

static long globalmem_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct globalmem_dev *dev = filp->private_data;

	switch (cmd) {

	case MEM_CLEAR:
		mutex_lock(&dev->mutex);
		memset(dev->mem, 0, GLOBALMEM_SIZE);
		mutex_unlock(&dev->mutex);
		printk("global memory set to zero\n");
		break;

	default:
		return -EINVAL;
	}

	return 0;
}

static int globalmem_open(struct inode *inode, struct file *filp)
{
	struct globalmem_dev *dev = container_of(inode->i_cdev, struct globalmem_dev, cdev);

	filp->private_data = dev;

	return 0;
}

static int globalmem_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static const struct file_operations globalmem_fops = {
	.owner = THIS_MODULE,
	.llseek = globalmem_llseek,
	.read = globalmem_read,
	.write = globalmem_write,
	.unlocked_ioctl = globalmem_ioctl,
	.open = globalmem_open,
	.release = globalmem_release,
};

static void globalmem_setup_cdev(struct globalmem_dev *dev, int index)
{
	int err, devno = MKDEV(globalmem_major, index);

	cdev_init(&dev->cdev, &globalmem_fops);
	dev->cdev.owner = THIS_MODULE;
	err = cdev_add(&dev->cdev, devno, 1);
	if (err)
		printk("adding globalmem_%d err:%d", index, err);

	mutex_init(&dev->mutex);
}

static int __init globalmem_init(void)
{
	int ret, i;
	dev_t devno = MKDEV(globalmem_major, 0);

	if (globalmem_major) {
		printk("register globalmem major: %d\n", globalmem_major);
		ret = register_chrdev_region(devno, DEVICE_NUM, DEV_NAME);
	} else {
		ret = alloc_chrdev_region(&devno, 0, DEVICE_NUM, DEV_NAME);
		globalmem_major = MAJOR(devno);
		printk("allocate globalmem major: %d\n", globalmem_major);
	}

	if (ret < 0)
		return ret;

	globalmem_devp = kzalloc(sizeof(struct globalmem_dev) * DEVICE_NUM, GFP_KERNEL);
	if (!globalmem_devp) {
		ret = -ENOMEM;
		goto fail_malloc;
	}

	for (i = 0; i < DEVICE_NUM; i++)
		globalmem_setup_cdev(globalmem_devp + i, i);

	printk("globalmem_init\n");
	return 0;

fail_malloc:
	unregister_chrdev_region(devno, DEVICE_NUM);
	return ret;
}
module_init(globalmem_init);

static void __exit globalmem_exit(void)
{
	int i;

	for (i = 0; i < DEVICE_NUM; i++)
		cdev_del(&(globalmem_devp + i)->cdev);

	kfree(globalmem_devp);

	unregister_chrdev_region(MKDEV(globalmem_major, 0), DEVICE_NUM);

	printk("globalmem_exit\n");
}
module_exit(globalmem_exit);

MODULE_AUTHOR("Henry.Zeng");
MODULE_DESCRIPTION("global memory");
MODULE_LICENSE("GPL v2");
MODULE_VERSION("1.0.0");
