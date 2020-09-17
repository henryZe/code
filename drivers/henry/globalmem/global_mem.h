#ifndef GLOBAL_MEM_H
#define GLOBAL_MEM_H

#define GLOBALMEM_SIZE 0x1000
#define DEVICE_NUM 10

#define GLOBALMEM_MAGIC 'm'
#define MEM_CLEAR _IO(GLOBALMEM_MAGIC, 0)

#define DEV_NAME "globalmem"

#endif
