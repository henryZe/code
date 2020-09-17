#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/poll.h>

#include "global_fifo.h"

static int globalfifo_major;
module_param(globalfifo_major, int, S_IRUGO);

struct globalfifo_dev {
	struct cdev cdev;
	unsigned int current_len;
	unsigned char mem[GLOBALFIFO_SIZE];
	struct mutex mutex;
	wait_queue_head_t r_wait;
	wait_queue_head_t w_wait;
	struct fasync_struct *async_queue;
	struct platform_device *parent;
};

struct globalfifo_dev *globalfifo_devp;

static loff_t globalfifo_llseek(struct file *filp, loff_t offset, int orig)
{
	loff_t ret = 0;

	switch (orig) {

	/* file pos beginning */
	case SEEK_SET:
		if (offset < 0) {
			ret = -EINVAL;
			break;
		}

		if ((unsigned int)offset > GLOBALFIFO_SIZE) {
			ret = -EINVAL;
			break;
		}

		filp->f_pos = (unsigned int)offset;
		ret = filp->f_pos;
		break;

	/* file pos current */
	case SEEK_CUR:
		if ((filp->f_pos + offset) > GLOBALFIFO_SIZE) {
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

static ssize_t globalfifo_read(struct file *filp,
	char __user *buf, size_t count, loff_t *ppos)
{
	int ret = 0;
	struct globalfifo_dev *dev = filp->private_data;
	DECLARE_WAITQUEUE(wait, current);

	mutex_lock(&dev->mutex);
	add_wait_queue(&dev->r_wait, &wait);

	while (!dev->current_len) {
		if (filp->f_flags & O_NONBLOCK) {
			ret = -EAGAIN;
			goto out;
		}
		/* not sleep yet */
		set_current_state(TASK_INTERRUPTIBLE);
		mutex_unlock(&dev->mutex);

		schedule();
		if (signal_pending(current)) {
			ret = -ERESTARTSYS;
			goto out2;
		}

		mutex_lock(&dev->mutex);
	}

	if (count > dev->current_len)
		count = dev->current_len;

	if (copy_to_user(buf, dev->mem, count)) {
		ret = -EFAULT;
		goto out;
	} else {
		memcpy(dev->mem, dev->mem + count, dev->current_len - count);
		dev->current_len -= count;
		printk("read %u byte(s) from %p\n", count, dev->mem + count);

		wake_up_interruptible(&dev->w_wait);
		ret = count;
	}

out:
	mutex_unlock(&dev->mutex);
out2:
	remove_wait_queue(&dev->r_wait, &wait);
	set_current_state(TASK_RUNNING);

	return ret;
}

static ssize_t globalfifo_write(struct file *filp,
	const char __user *buf, size_t count, loff_t *ppos)
{
	int ret = 0;
	struct globalfifo_dev *dev = filp->private_data;
	DECLARE_WAITQUEUE(wait, current);

	mutex_lock(&dev->mutex);
	add_wait_queue(&dev->w_wait, &wait);

	while (dev->current_len == GLOBALFIFO_SIZE) {
		if (filp->f_flags & O_NONBLOCK) {
			ret = -EAGAIN;
			goto out;
		}
		/* not sleep yet */
		set_current_state(TASK_INTERRUPTIBLE);
		mutex_unlock(&dev->mutex);

		schedule();
		if (signal_pending(current)) {
			ret = -ERESTARTSYS;
			goto out2;
		}

		mutex_lock(&dev->mutex);
	}

	if (count > GLOBALFIFO_SIZE - dev->current_len)
		count = GLOBALFIFO_SIZE - dev->current_len;

	if (copy_from_user(dev->mem + dev->current_len, buf, count)) {
		ret = -EFAULT;
		goto out;
	} else {
		printk("write %u byte(s) to %p\n", count, dev->mem + dev->current_len);
		dev->current_len += count;

		wake_up_interruptible(&dev->r_wait);

		if (dev->async_queue) {
			kill_fasync(&dev->async_queue, SIGIO, POLL_IN);
			printk("%s kill SIGIO\n", __func__);
		}

		ret = count;
	}

out:
	mutex_unlock(&dev->mutex);
out2:
	remove_wait_queue(&dev->w_wait, &wait);
	set_current_state(TASK_RUNNING);

	return ret;
}

static long globalfifo_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct globalfifo_dev *dev = filp->private_data;

	switch (cmd) {

	case MEM_CLEAR:
		memset(dev->mem, 0, GLOBALFIFO_SIZE);
		printk("global memory set to zero\n");
		break;

	default:
		return -EINVAL;
	}

	return 0;
}

static int globalfifo_open(struct inode *inode, struct file *filp)
{
	struct globalfifo_dev *dev = container_of(inode->i_cdev, struct globalfifo_dev, cdev);

	filp->private_data = dev;

	return 0;
}

static int globalfifo_fasync(int fd, struct file *filp, int mode)
{
	struct globalfifo_dev *dev = filp->private_data;

	return fasync_helper(fd, filp, mode, &dev->async_queue);
}

static int globalfifo_release(struct inode *inode, struct file *filp)
{
	globalfifo_fasync(-1, filp, 0);

	return 0;
}

static unsigned int globalfifo_poll(struct file *filp, poll_table *wait)
{
	unsigned int mask = 0;
	struct globalfifo_dev *dev = filp->private_data;

	mutex_lock(&dev->mutex);

	poll_wait(filp, &dev->r_wait, wait);
	poll_wait(filp, &dev->w_wait, wait);

	if (dev->current_len)
		mask |= POLLIN | POLLRDNORM;

	if (dev->current_len != GLOBALFIFO_SIZE)
		mask |= POLLOUT | POLLWRNORM;

	mutex_unlock(&dev->mutex);

	return mask;
}

static const struct file_operations globalfifo_fops = {
	.owner = THIS_MODULE,
	.llseek = globalfifo_llseek,
	.read = globalfifo_read,
	.write = globalfifo_write,
	.unlocked_ioctl = globalfifo_ioctl,
	.open = globalfifo_open,
	.release = globalfifo_release,

	.poll = globalfifo_poll,
	.fasync = globalfifo_fasync,
};

static void globalfifo_setup_cdev(struct globalfifo_dev *dev, int index)
{
	int err, devno = MKDEV(globalfifo_major, index);

	cdev_init(&dev->cdev, &globalfifo_fops);
	dev->cdev.owner = THIS_MODULE;
	err = cdev_add(&dev->cdev, devno, 1);
	if (err)
		dev_info(&dev->parent->dev, "adding globalfifo_%d err:%d", index, err);

	mutex_init(&dev->mutex);
	init_waitqueue_head(&dev->r_wait);
	init_waitqueue_head(&dev->w_wait);
	dev->current_len = 0;
}

static int globalfifo_probe(struct platform_device *pdev)
{
	int ret, i;
	dev_t devno = MKDEV(globalfifo_major, 0);

	if (globalfifo_major) {
		dev_info(&pdev->dev, "register globalfifo major: %d\n", globalfifo_major);
		ret = register_chrdev_region(devno, DEVICE_NUM, DEV_NAME);
	} else {
		ret = alloc_chrdev_region(&devno, 0, DEVICE_NUM, DEV_NAME);
		globalfifo_major = MAJOR(devno);
		dev_info(&pdev->dev, "allocate globalfifo major: %d\n", globalfifo_major);
	}

	if (ret < 0)
		return ret;

	globalfifo_devp = devm_kzalloc(&pdev->dev, sizeof(struct globalfifo_dev) * DEVICE_NUM, GFP_KERNEL);
	if (!globalfifo_devp) {
		ret = -ENOMEM;
		goto fail_malloc;
	}

	for (i = 0; i < DEVICE_NUM; i++) {
		globalfifo_devp[i].parent = pdev;
		globalfifo_setup_cdev(globalfifo_devp + i, i);
	}

	dev_info(&pdev->dev, "globalfifo_probe\n");
	return 0;

fail_malloc:
	unregister_chrdev_region(devno, DEVICE_NUM);
	return ret;
}

static int globalfifo_remove(struct platform_device *pdev)
{
	int i;

	for (i = 0; i < DEVICE_NUM; i++)
		cdev_del(&(globalfifo_devp + i)->cdev);

	unregister_chrdev_region(MKDEV(globalfifo_major, 0), DEVICE_NUM);

	dev_info(&pdev->dev, "globalfifo_remove\n");

	return 0;
}

static const struct of_device_id globalfifo_of_match[] = {
{ .compatible = "henry,globalfifo", },
	 {},
};
MODULE_DEVICE_TABLE(of, globalfifo_of_match);

static struct platform_driver globalfifo_driver = {
	.driver = {
		.name = "globalfifo",
		.owner = THIS_MODULE,
		.of_match_table = globalfifo_of_match,
	},
	.probe = globalfifo_probe,
	.remove = globalfifo_remove,
};

module_platform_driver(globalfifo_driver);

MODULE_AUTHOR("Henry.Zeng");
MODULE_DESCRIPTION("global fifo");
MODULE_LICENSE("GPL v2");
MODULE_VERSION("1.0.0");
