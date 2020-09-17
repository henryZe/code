#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <strings.h>
#include <sys/epoll.h>

#include "global_fifo.h"

void main(void)
{
	int fd;
	struct epoll_event ev_fifo;
	int err;
	int epoll_fd;

	fd = open("/dev/globalfifo", O_RDONLY | O_NONBLOCK);
	if (fd != -1) {
		if (ioctl(fd, MEM_CLEAR, 0) < 0)
			printf("ioctl command failed\n");

		epoll_fd = epoll_create(1);
		if (epoll_fd < 0) {
			printf("epoll create failed\n");
			return;
		}

		bzero(&ev_fifo, sizeof(ev_fifo));
		ev_fifo.events = EPOLLIN;

		err = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev_fifo);
		if (err) {
			printf("epoll ctl failed\n");
			return;
		}

		/* time out = 1s */
		while (1) {
			err = epoll_wait(epoll_fd, &ev_fifo, 1, 1000);
			if (err < 0) {
				printf("epoll wait failed\n");
				return;
			} else if (!err)
				printf("No input within 1 second\n");
			else
				printf("FIFO isn't empty\n");
		}
	} else
		printf("device open failed\n");
}
