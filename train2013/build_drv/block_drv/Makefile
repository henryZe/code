obj-m += block_drv.o

KERNEL = /opt/build_kernel/teacher/android-kernel-samsung-dev

all:
	make modules -C $(KERNEL) M=`pwd`
#arm-linux-gcc app.c -o app
	cp block_drv.ko /tftpboot/arm_rootfs/my_driver
#cp app /tftpboot/arm_rootfs/my_driver
