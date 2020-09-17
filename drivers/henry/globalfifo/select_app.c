#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#include "global_fifo.h"

void main(void)
{
	int fd, num;
	fd_set rfds, wfds;

	fd = open("/dev/globalfifo", O_RDONLY | O_NONBLOCK);
	if (fd != -1) {
		if (ioctl(fd, MEM_CLEAR, 0) < 0)
			printf("ioctl command failed\n");

		while (1) {
			FD_ZERO(&rfds);
			FD_ZERO(&wfds);
			FD_SET(fd, &rfds);
			FD_SET(fd, &wfds);

			select(fd + 1, &rfds, &wfds, NULL, NULL);
			if (FD_ISSET(fd, &rfds))
				printf("poll %d: can be read\n", getpid());
			if (FD_ISSET(fd, &wfds))
				printf("poll %d: can be written\n", getpid());

			sleep(1);
		}
	} else
		printf("device open failed\n");
}
