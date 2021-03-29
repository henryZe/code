obj-m += net_drv.o net_dev.o just_try.o

KERNEL = /opt/build_kernel/teacher/android-kernel-samsung-dev

all:
	make modules -C $(KERNEL) M=`pwd`
	cp net_drv.ko /tftpboot/arm_rootfs/my_driver
	cp net_dev.ko /tftpboot/arm_rootfs/my_driver
	cp just_try.ko /tftpboot/arm_rootfs/my_driver
