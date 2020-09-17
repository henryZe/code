#ifndef GLOBAL_FIFO_H
#define GLOBAL_FIFO_H

#include <linux/ioctl.h>

#define GLOBALFIFO_SIZE 0x1000
#define DEVICE_NUM 10

#define GLOBALFIFO_MAGIC 'f'
#define MEM_CLEAR _IO(GLOBALFIFO_MAGIC, 0)

#define DEV_NAME "globalfifo"

#endif
