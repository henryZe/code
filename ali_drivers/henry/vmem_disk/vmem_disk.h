#ifndef VMEM_DISK_H
#define VMEM_DISK_H

#define VMEM_DISK_MINORS 1

#define N_DEVICES 4

#define N_SECTORS 4096
#define HWSECTOR_SIZE 512
#define KERNEL_SECTOR_SIZE 512

#define VMEMD_NOQUEUE 0
#define VMEMD_QUEUE 1

#define DEV_NAME "vmem_disk"

#endif
