#include <linux/types.h>
#include <linux/device.h>
#include "ali_henry_drv_sys.h"
#include "../../base/base.h"

#define LINK_NAME "henry_sys_link"

static ssize_t att_show_debug_mode(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct henry_drv *drv = dev_get_drvdata(dev);
	ssize_t count = 0;

	mutex_lock(&drv->mutex);
	count += sprintf(buf, "debug_mode: %d\n", drv->debug_mode);
	mutex_unlock(&drv->mutex);

	return count;
}

static ssize_t att_store_debug_mode(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	int ret;
	struct henry_drv *drv = dev_get_drvdata(dev);
	int debug_mode;

	if (kstrtoint(buf, 10, &debug_mode))
		return -EINVAL;

	mutex_lock(&drv->mutex);
	drv->debug_mode = (debug_mode & 0x01);
	mutex_unlock(&drv->mutex);

	ret = kobject_uevent(&dev->kobj, KOBJ_CHANGE);
	if (unlikely(ret))
		dev_info(drv->dev, "kobject_uevent failed\n");

	return count;
}

static DEVICE_ATTR(debug_mode_single, 0666, att_show_debug_mode, att_store_debug_mode);
static DEVICE_ATTR(debug_mode, 0666, att_show_debug_mode, att_store_debug_mode);

static const struct attribute *sysfs_attrs[] = {
	&dev_attr_debug_mode.attr,
	/* end with NULL */
	NULL,
};

int henry_sysfs_create(struct henry_drv *drv)
{
	int ret = 0;

	ret = sysfs_create_file(&drv->dev->kobj, &dev_attr_debug_mode_single.attr);
	if (ret)
		dev_info(drv->dev, "sysfs create file failed\n");

	ret = sysfs_create_files(&drv->dev->kobj, sysfs_attrs);
	if (ret)
		dev_info(drv->dev, "sysfs create files failed\n");

	ret = sysfs_create_link(&drv->dev_class->p->subsys.kobj, &drv->dev->kobj, LINK_NAME);
	if (ret)
		dev_info(drv->dev, "sysfs create link failed\n");

	return ret;
}

void henry_sysfs_remove(struct henry_drv *drv)
{
	sysfs_remove_link(&drv->dev_class->p->subsys.kobj, LINK_NAME);
	sysfs_remove_file(&drv->dev->kobj, &dev_attr_debug_mode_single.attr);
	sysfs_remove_files(&drv->dev->kobj, sysfs_attrs);
}
