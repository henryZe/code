cmd_/opt/build_drv/practice/sub.o := /usr/local/arm/arm-2009q3/bin/arm-none-linux-gnueabi-gcc -Wp,-MD,/opt/build_drv/practice/.sub.o.d  -nostdinc -isystem /usr/local/arm/arm-2009q3/bin/../lib/gcc/arm-none-linux-gnueabi/4.4.1/include -I/opt/build_kernel/teacher/android-kernel-samsung-dev/arch/arm/include -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-s5pv210/include -Iarch/arm/plat-s5p/include -Iarch/arm/plat-samsung/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -marm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -mabi=aapcs-linux -mno-thumb-interwork -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1024 -fno-stack-protector -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack  -DMODULE -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(sub)"  -D"KBUILD_MODNAME=KBUILD_STR(main_sub)"  -c -o /opt/build_drv/practice/sub.o /opt/build_drv/practice/sub.c

deps_/opt/build_drv/practice/sub.o := \
  /opt/build_drv/practice/sub.c \

/opt/build_drv/practice/sub.o: $(deps_/opt/build_drv/practice/sub.o)

$(deps_/opt/build_drv/practice/sub.o):
