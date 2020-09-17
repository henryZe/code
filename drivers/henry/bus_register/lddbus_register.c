#include <linux/module.h>
#include <linux/device.h>

#include "lddbus.h"

static char *Version = "1.0";

static int ldd_match(struct device *dev, struct device_driver *driver)
{
	return !strncmp(dev->init_name, driver->name, strlen(driver->name));
}

static int ldd_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	env->envp[0] = env->buf;
	if (snprintf(env->buf, env->buflen, "LDDBUS_VERSION is %s", Version) >= env->buflen)
		return -ENOMEM;
	env->envp[1] = NULL;

	return 0;
}

struct bus_type ldd_bus_type = {
	.name = "ldd",
	.match = ldd_match,
	.uevent  = ldd_uevent,
};

static ssize_t show_bus_version(struct bus_type *bus, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%s\n", Version);
}

static BUS_ATTR(version, S_IRUGO, show_bus_version, NULL);

static void ldd_bus_release(struct device *dev)
{
	pr_info("lddbus release\n");
}

struct device ldd_bus = {
	.init_name = "ldd0",
	.release = ldd_bus_release
};

static int __init ldd_bus_init(void)
{
	int ret;

	ret = bus_register(&ldd_bus_type);
	if (ret)
		return ret;

	pr_info("lddbus register\n");

	if (bus_create_file(&ldd_bus_type, &bus_attr_version))
		pr_err("Unable to create version attribute\n");

	pr_info("lddbus attribute version create\n");

	ret = device_register(&ldd_bus);
	if (ret)
		pr_err("Unable to register ldd0\n");

	pr_info("ldd0 register\n");

	return ret;
}

static void ldd_bus_exit(void)
{
	device_unregister(&ldd_bus);
	pr_info("ldd0 unregister\n");

	bus_unregister(&ldd_bus_type);
	pr_info("lddbus unregister\n");
}

module_init(ldd_bus_init);
module_exit(ldd_bus_exit);

void ldd_dev_release(struct device *dev)
{
	pr_info("%s release\n", dev->init_name);
}

int register_ldd_device(struct ldd_device *ldddev)
{
	ldddev->dev.bus = &ldd_bus_type;
	ldddev->dev.parent = &ldd_bus;
	ldddev->dev.release = ldd_dev_release;
	ldddev->dev.init_name = ldddev->name;

	return device_register(&ldddev->dev);
}
EXPORT_SYMBOL(register_ldd_device);

void unregister_ldd_device(struct ldd_device *ldddev)
{
	device_unregister(&ldddev->dev);
}
EXPORT_SYMBOL(unregister_ldd_device);

static ssize_t show_version(struct device_driver *driver, char *buf)
{
	struct ldd_driver *ldd_driver = driver_to_ldd_driver(driver);

	sprintf(buf, "%s\n", ldd_driver->version);
	return strlen(buf);
}

int register_ldd_driver(struct ldd_driver *driver)
{
	int ret;

	driver->driver.bus = &ldd_bus_type;
	ret = driver_register(&driver->driver);
	if (ret)
		return ret;

	driver->version_attr.attr.name = "version";
	driver->version_attr.attr.mode = S_IRUGO;
	driver->version_attr.show = show_version;
	driver->version_attr.store = NULL;

	return driver_create_file(&driver->driver, &driver->version_attr);
}
EXPORT_SYMBOL(register_ldd_driver);

MODULE_AUTHOR("Henry.Zeng");
