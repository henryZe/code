obj-m += add.o

obj-m += main_sub.o
main_sub-objs := module.o sub.o


KERNEL = /opt/build_kernel/teacher/android-kernel-samsung-dev

all:
	make modules -C $(KERNEL) M=`pwd`
clean:
	make modules clean -C $(KERNEL) M=`pwd`

cp:
	cp *.ko /tftpboot/arm_rootfs
