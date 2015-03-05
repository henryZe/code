obj-m += char_drv.o

KERNEL = /opt/build_kernel/teacher/android-kernel-samsung-dev

all:
	make modules -C $(KERNEL) M=`pwd`
	cp char_drv.ko /tftpboot/arm_rootfs/my_driver
