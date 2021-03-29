#ifndef LDDBUS_H
#define LDDBUS_H

struct ldd_device {
	char *name;
	struct ldd_driver *driver;
	struct device dev;
};

#define device_to_ldd_device(dev) container_of(dev, struct ldd_device, dev);

struct ldd_driver {
	char *version;
	struct module *module;
	struct device_driver driver;
	struct driver_attribute version_attr;
};

#define driver_to_ldd_driver(drv) container_of(drv, struct ldd_driver, driver);

int register_ldd_device(struct ldd_device *ldddev);
void unregister_ldd_device(struct ldd_device *ldddev);

int register_ldd_driver(struct ldd_driver *ldddrv);

#endif
