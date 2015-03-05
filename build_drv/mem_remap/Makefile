obj-m += char_drv.o

KERNEL = /opt/build_kernel/teacher/android-kernel-samsung-dev

all:
	make modules -C $(KERNEL) M=`pwd`
	arm-linux-gcc app.c -o app
	cp char_drv.ko /tftpboot/arm_rootfs/my_driver
	cp app /tftpboot/arm_rootfs/my_driver

clean:
	make modules clean -C  $(KERNEL)  M=`pwd`
