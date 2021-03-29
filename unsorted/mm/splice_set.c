#include <inttypes.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#define __USE_GNU
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>

#define PAGE_SIZE 4096

int main(int argc, char **argv)
{
	void *addr;
	int i, p, ret = 0;
	struct iovec iov;
	int input_fd, src_fd, dst_fd;
	int p1[2], p2[2];
	int tran_size, file_size = 0;
	int n_page = 0;
	char buffer[PAGE_SIZE];

	ret = pipe(p1);
	if(ret)
		perror("pipe");
	ret = pipe(p2);
	if(ret)
		perror("pipe");

	input_fd = open("./input_file", O_RDWR);
	if (input_fd < 0)
		perror("open");
	
	src_fd = open("./memory", O_CREAT|O_RDWR|O_TRUNC, 0766);
	if (src_fd < 0)
		perror("open dst");

	dst_fd = open("./output_file", O_CREAT|O_RDWR|O_TRUNC, 0766);
	if (dst_fd < 0)
		perror("open dst");

	file_size = lseek(input_fd, 0, SEEK_END);
	printf("file_size: %d\n", file_size);
	lseek(input_fd, 0, SEEK_SET);
	
/*	n_page = (file_size+PAGE_SIZE-1)/PAGE_SIZE;

	for(i = 0, p = 0; i < n_page; i++, p+=ret) {
		
		// fd -> pipe
		ret = splice(input_fd, 0, p1[1], 0, PAGE_SIZE, SPLICE_F_MOVE);
		if (ret < 0) {
			perror("write splice");
			return -1;
		}
		printf("write splice ret = %d\n", ret);

		iov.iov_base = buffer;
		iov.iov_len = ret;

		// pipe -> user_mm
		ret = vmsplice(p1[0], &iov, 1, 0);
		if (ret < 0) {
			perror("write vmsplice");
			return -1;
		}
		printf("write vmsplice ret = %d\n", ret);

		// user_mm -> fd
		ret = write(src_fd, buffer, ret);
		if (ret < 0) {
			perror("write");
			return -1;
		}
	}*/

/*	for(i = 0, p = 0; i < n_page; i++, p+=ret) {
		
		// fd -> mm
		addr = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE, src_fd, p);
		if (addr == MAP_FAILED) {
			perror("mmap");
			return -1;
		}

		iov.iov_base = addr;
		iov.iov_len = file_size>PAGE_SIZE? PAGE_SIZE:file_size;

		// mm -> pipe
		ret = vmsplice(p2[1], &iov, 1, 0);
		if (ret < 0) {
			perror("vmsplice");
			return -1;
		}
		printf("vmsplice ret = %d\n", ret);
		
		// pipe -> fd
		ret = splice(p2[0], 0, dst_fd, 0, ret, SPLICE_F_MOVE);
		if (ret < 0) {
			perror("splice");
			return -1;
		}
		printf("splice ret = %d\n", ret);

		file_size -= ret;
		
		munmap(addr, PAGE_SIZE);
	}*/

	lseek(input_fd, 0, SEEK_SET);
	/*ret = sendfile(dst_fd, input_fd, NULL, file_size);
	if (ret < 0) {
			perror("sendfile");
			return -1;
		}
	printf("sendfile ret = %d\n", ret);*/

	ret = splice(input_fd, NULL, p1[1], NULL, file_size, SPLICE_F_MOVE);
	if (ret < 0) {
 		perror("splice");
 		return -1;
	}
	printf("read splice ret = %d\n", ret);
	
	ret = tee(p1[0], p2[1], file_size, 0);
	if (ret < 0) {
		perror("tee");
		return -1;
	}
	printf("tee ret = %d\n", ret);

	ret = splice(p2[0], NULL, dst_fd, NULL, ret, SPLICE_F_MOVE);
	if (ret < 0) {
		perror("splice");
		return -1;
	}
	printf("write splice ret = %d\n", ret);

	close(input_fd);
	close(src_fd);
	close(dst_fd);

	return 0;
}
