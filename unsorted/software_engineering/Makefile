all:
	gcc -o output/w.o -c w.c
	gcc -o output/s.o -c s.c

	ar rcs output/libw.a output/w.o
	ar rcs output/libs.a output/s.o

	gcc -o output/main.elf main.c -L./output -Wl,--whole-archive -lw -ls -Wl,--no-whole-archive
	# gcc -o output/main.elf main.c -L./output -lw -ls

	objdump -S output/main.elf > output/main.asm
	readelf -a output/main.elf > output/main.txt

clean:
	rm output/*
