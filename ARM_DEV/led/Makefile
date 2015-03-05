all:led.bin clean

led.bin:led.o
	arm-linux-ld -Ttext=0x40000000 led.o -o led.elf
	arm-linux-objcopy -O binary -S led.elf led.bin

led.o:led.c
	arm-linux-gcc -c -nostdlib led.c -o led.o

clean:
	cp ./led.bin /tftpboot
	rm -rf ./*.o ./*.elf ./*.bin 
