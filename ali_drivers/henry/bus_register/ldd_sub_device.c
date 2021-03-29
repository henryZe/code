#include <linux/module.h>
#include <linux/device.h>
#include <linux/cdev.h>

#include "lddbus.h"

struct ldd_sub_dev {
	char devname[8];
	struct ldd_device ldd_device;
	struct cdev cdev;
};

static ssize_t sub_device_show_dev(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct ldd_sub_dev *sub_dev = dev->driver_data;

	return print_dev_t(buf, sub_dev->cdev.dev);
}

static DEVICE_ATTR(dev, S_IRUGO, sub_device_show_dev, NULL);

static void ldd_sub_device_register(struct ldd_sub_dev *dev, int index)
{
	sprintf(dev->devname, "sub%d", index);
	dev->ldd_device.name = dev->devname;
	dev->ldd_device.driver = NULL;
	dev->ldd_device.dev.driver_data = dev;
	register_ldd_device(&dev->ldd_device);
	device_create_file(&dev->ldd_device.dev, &dev_attr_dev);	
}

static struct ldd_sub_dev sub_dev;

static struct ldd_driver sub_driver = {
	.version = "version 1.0",
	.module = THIS_MODULE,
	.driver = {
		.name = "ldd_driver",
	},
};

static void ldd_sub_driver_register(struct ldd_driver *sub_driver)
{
	register_ldd_driver(sub_driver);
}

int __init sub_dev_init(void)
{
	ldd_sub_device_register(&sub_dev, 0);
	pr_info("sub device init\n");

	ldd_sub_driver_register(&sub_driver);
	pr_info("sub driver init\n");

	return 0;
}

module_init(sub_dev_init);

MODULE_AUTHOR("Henry.Zeng");
