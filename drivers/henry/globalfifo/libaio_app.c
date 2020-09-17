#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <libaio.h>

#define BUF_SIZE 4096

int main(int argc, char **argv)
{
	io_context_t ctx = 0;
	struct iocb cb;
	struct iocb *cbs[1];
	unsigned char *buf;
	struct io_event events[1];
	int ret;
	int fd;

	if (argc < 2) {
		printf("error format: aior [FILE]\n");
		exit(1);
	}

	/* O_DIRECT means copy user data to disk directly
		without through by kernel buffer.
	*/
	fd = open(argv[1], O_RDWR | O_DIRECT);
	if (fd < 0) {
		printf("open error\n");
		goto err;
	}

	/* O_DIRECT requests user data must be aligned in block size. */
	ret = posix_memalign((void **)&buf, 512, (BUF_SIZE + 1));
	if (ret < 0) {
		printf("posix_memalign failed\n");
		goto err1;
	}
	memset(buf, 0, BUF_SIZE + 1);

	ret = io_setup(128, &ctx);
	if (ret < 0) {
		printf("io_setup failed\n");
		goto err2;
	}

	io_prep_pread(&cb, fd, buf, BUF_SIZE, 0);

	cbs[0] = &cb;
	ret = io_submit(ctx, 1, cbs);
	if (ret < 0) {
		printf("io_submit failed\n");
		goto err3;
	}

	/* blocking here */
	ret = io_getevents(ctx, 1, 1, events, NULL);
	if (ret < 0) {
		printf("io_getevents failed\n");
		goto err3;
	}

	if (!events[0].res2)
		/* read success */
		printf("%s\n", buf);
	else {
		printf("AIO error: %s\n", strerror(-events[0].res));
		goto err3;
	}

	ret = io_destroy(ctx);
	if (ret < 0) {
		printf("io_destroy failed\n");
		goto err2;
	}

	free(buf);
	close(fd);

	return 0;

err3:
	ret = io_destroy(ctx);
	if (ret < 0)
		printf("io_destroy failed\n");

err2:
	free(buf);

err1:
	close(fd);

err:
	return -1;
}
