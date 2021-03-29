#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/epoll.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/eventfd.h>
#define __USE_GNU
#include <fcntl.h>

#define DEBUG printf

#define MAX_EVENTS 1
#define BUFF_SIZE_SEND (100)
#define BUFF_SIZE_RECV (100)

int splice_way(int file_size, int asa_sess, int src_fd, int dst_fd)
{
	int ret = 0;
	int epollfd;
	int nfds;
	int p1[2], p2[2];
	struct epoll_event ev, events[MAX_EVENTS];
	int write_time = 0;
	int read_time = 0;

	epollfd = epoll_create(1);
	if (epollfd == -1) {
		perror("epoll_create");
		exit(EXIT_FAILURE);
	}

	/* available to operate */
	ev.events = EPOLLOUT | EPOLLIN;
	ev.data.fd = asa_sess;
	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, asa_sess, &ev) == -1) {
		perror("epoll_add");
		exit(EXIT_FAILURE);
	}

	ret = pipe(p1);
	if (ret)
		perror("pipe");
	ret = pipe(p2);
	if (ret)
		perror("pipe");

	while (1) {
		if (file_size) {
			nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
			if (nfds == -1) {
				perror("epoll_pwait");
				exit(EXIT_FAILURE);
			}

			if (events[0].events & EPOLLIN) {
				DEBUG("read before\n");
				ret = splice(asa_sess, 0, p2[1], 0, BUFF_SIZE_RECV, SPLICE_F_MOVE);
				if (ret < 0)
					perror("read error");

				read_time++;
				DEBUG("read: %d ret = %d\n", read_time, ret);

				ret = splice(p2[0], 0, dst_fd, 0, ret, SPLICE_F_MOVE);
				if (ret < 0)
					perror("splice");

				file_size -= ret;
			} else if (events[0].events & EPOLLOUT) {
				ret = splice(src_fd, 0, p1[1], 0, BUFF_SIZE_SEND, SPLICE_F_MOVE);

				if (ret < 0)
					perror("read error");
				else if (!ret) {
					DEBUG("end of input\n");

					ev.events = EPOLLIN;
					epoll_ctl(epollfd, EPOLL_CTL_DEL, asa_sess, &ev);
					if (epoll_ctl(epollfd, EPOLL_CTL_ADD, asa_sess, &ev) == -1) {
						perror("epoll_add");
						exit(EXIT_FAILURE);
					}

					continue;
				} else {
					DEBUG("write before\n");
					ret = splice(p1[0], 0, asa_sess, 0, ret, SPLICE_F_MOVE);
					if (ret < 0)
						perror("splice");

					write_time++;
					DEBUG("write: %d ret = %d\n", write_time, ret);
				}
			}
		} else
			break;
	}

	close(p1[0]);
	close(p1[1]);
	close(p2[0]);
	close(p2[1]);

	ret = close(epollfd);
	if (ret)
		perror("close epollfd");

	return 0;
}

int main()
{
	int ret;
	int dev_fd, fd_in, fd_out, size;
	int pp[2];
	const char *in_name = "/mnt/nfs/in";
	const char *out_name = "/mnt/nfs/out";
	const char *dev_name = "/dev/henry";

	fd_in = open(in_name, O_RDONLY);
	if (fd_in < 0)
		perror("open src");

	size = lseek(fd_in, 0, SEEK_END);
	printf("file_size: %d\n", size);
	lseek(fd_in, 0, SEEK_SET);

	fd_out = open(out_name, O_CREAT|O_RDWR|O_TRUNC, 0766);
	if (fd_out < 0)
		perror("open dst");

	dev_fd = open(dev_name, O_RDWR, 0766);
	if (dev_fd < 0)
		perror("open dev");

	splice_way(size, dev_fd, fd_in, fd_out);

	close(fd_in);
	close(fd_out);

	close(dev_fd);

	return 0;
}
