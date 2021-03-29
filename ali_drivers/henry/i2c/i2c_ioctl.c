#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

int main(int argc, char **argv)
{
	int fd, i, ret;
	unsigned char val;
	unsigned int slave_addr, reg_addr;
	struct i2c_rdwr_ioctl_data work_queue;

	if (argc < 4) {
		printf("Use:\n%s /dev/i2c-x slave_addr reg_addr\n", argv[0]);
		return 0;
	}

	fd = open(argv[1], O_RDWR);
	if (!fd) {
		printf("open failed\n");
		return 0;
	}

	sscanf(argv[1], "%d", &slave_addr);
	sscanf(argv[2], "%d", &reg_addr);

	work_queue.nmsgs = 2;
	work_queue.msgs = (struct i2c_msg *)malloc(work_queue.nmsgs * sizeof(struct i2c_msg));
	if (!work_queue.msgs) {
		printf("malloc failed\n");
		close(fd);
		return 0;
	}

	ioctl(fd, I2C_TIMEOUT, 1);
	ioctl(fd, I2C_RETRIES, 1);

	for (i = reg_addr; i < (reg_addr + 16); i++) {
		val = i;

		(work_queue.msgs[0]).len = 1;
		(work_queue.msgs[0]).addr = slave_addr;
		(work_queue.msgs[0]).buf = &val;

		(work_queue.msgs[1]).len = 1;
		(work_queue.msgs[1]).flags = I2C_M_RD;
		(work_queue.msgs[1]).addr = slave_addr;
		(work_queue.msgs[1]).buf = &val;

		ret = ioctl(fd, I2C_RDWR, (unsigned long)&work_queue);
		if (ret < 0)
			perror("error during I2C_RDWR");
		else
			printf("reg:%02x val:%02x\n", i, val);
	}

	close(fd);
	return 0;
}
