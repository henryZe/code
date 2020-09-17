#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#define BUFF_SIZE 32

int main(int argc, char **argv)
{
	unsigned int fd, idx;
	unsigned short mem_addr;
	unsigned short size;
	char buf[BUFF_SIZE];
	char cswap;
	union {
		unsigned short addr;
		char bytes[2];
	} tmp;

	if (argc < 4) {
		printf("Use:\n%s /dev/i2c-x mem_addr size\n", argv[0]);
		return 0;
	}

	sscanf(argv[1], "%hd", &mem_addr);
	sscanf(argv[2], "%hd", &size);

	if (size > BUFF_SIZE)
		size = BUFF_SIZE;

	fd = open(argv[1], O_RDWR);
	if (!fd) {
		printf("open failed\n");
		return 0;
	}

	ioctl(fd, I2C_SLAVE, 0x50);
	ioctl(fd, I2C_TIMEOUT, 1);
	ioctl(fd, I2C_RETRIES, 1);

	for (idx = 0; idx < size; ++idx, ++mem_addr) {
		tmp.addr = mem_addr;
		cswap = tmp.bytes[0];
		tmp.bytes[0] = tmp.bytes[1];
		tmp.bytes[1] = cswap;
		write(fd, &tmp.addr, 2);
		read(fd, &buf[idx], 1);
	}

	buf[size] = 0;
	close(fd);
	printf("Read %d char: %s\n", size, buf);

	return 0;
}
