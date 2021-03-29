#ifndef SECOND_DEVICE_H
#define SECOND_DEVICE_H

#include <linux/ioctl.h>

#define SECOND_MAGIC 's'
#define MEM_CLEAR _IO(SECOND_MAGIC, 0)

#define DEV_NAME "second"

#endif
