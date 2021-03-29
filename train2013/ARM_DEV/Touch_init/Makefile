CC = arm-linux-gcc
LD = arm-linux-ld
OBJCOPY = arm-linux-objcopy

CPPFLAGS = -nostdinc -nostdlib -I$(shell pwd)/include
CFLAGS = -fno-builtin -Wall -O2
LDS = armplat.lds

API_C = $(wildcard api/*.c)
API = $(patsubst %c,%o,$(API_C))
LIB = lib/uart.o lib/libc.a
CPU = cpu/start.o cpu/stack.o cpu/delay.o cpu/loop_print.o cpu/dis_cpsr.o cpu/dis_cp15.o cpu/api.o


all:start.bin clean

start.bin:$(LIB) $(CPU) $(API)
	$(LD) -T$(LDS) $(CPU) $(LIB) $(API) -o start.elf
	$(OBJCOPY) -O binary -S start.elf $@

%.o:%.c 
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

%.o:%.S
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@
	
clean:
	cp ./start.bin /tftpboot
	rm -rf ./start.o ./*elf 

