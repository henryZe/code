#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int ret;
	int fd;
	int counter, old_counter = 0;

	fd = open("/dev/second", O_RDONLY);
	if (fd < 0) {
		perror("open failed");
		goto err;
	} else {
		while(1) {
			ret = read(fd, (void *)&counter, sizeof(int));
			if (ret < 0) {
				printf("read failed\n");
				goto err1;
			}

			if (counter != old_counter) {
				printf("%d second(s) from open second to now\n", counter);
				old_counter = counter;
			}
		}
	}

err1:
	close(fd);

err:
	return -1;
}
