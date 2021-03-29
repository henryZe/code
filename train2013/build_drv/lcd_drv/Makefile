obj-m += lcd_drv.o lcd_dev.o

KERNEL = /opt/build_kernel/teacher/android-kernel-samsung-dev

all:
	make modules -C $(KERNEL) M=`pwd`
	arm-linux-gcc app.c -o app
	cp lcd_drv.ko /tftpboot/arm_rootfs/my_driver
	cp lcd_dev.ko /tftpboot/arm_rootfs/my_driver
	cp app /tftpboot/arm_rootfs/my_driver
