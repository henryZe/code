#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <errno.h>

#define MAX_PAYLOAD 1024
#define NETLINK_TEST 17

int main()
{
	int sock_fd, ret;
	struct sockaddr_nl src_addr, dest_addr;
	struct nlmsghdr *nlh = NULL;
	struct iovec iov;
	struct msghdr msg;

	sock_fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_TEST);

	memset(&src_addr, 0, sizeof(src_addr));
	src_addr.nl_family = AF_NETLINK;
	src_addr.nl_pid = getpid();
	src_addr.nl_groups = 0;

	ret = bind(sock_fd, (struct sockaddr *)&src_addr, sizeof(src_addr));
	if (ret < 0)
		perror("bind");

	memset(&dest_addr, 0, sizeof(dest_addr));
	dest_addr.nl_family = AF_NETLINK;
	dest_addr.nl_pid = 0;
	dest_addr.nl_groups = 0;

	nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PAYLOAD));
	nlh->nlmsg_len = NLMSG_SPACE(MAX_PAYLOAD);
	nlh->nlmsg_pid = getpid();
	nlh->nlmsg_flags = 0;
	strcpy(NLMSG_DATA(nlh), "Hello from userspace!");

	iov.iov_base = (void *)nlh;
	iov.iov_len = nlh->nlmsg_len;

	memset(&msg, 0, sizeof(msg));
	msg.msg_name = (void *)&dest_addr;
	msg.msg_namelen = sizeof(dest_addr);
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;

	ret = sendmsg(sock_fd, &msg, 0);
	if (ret != nlh->nlmsg_len)
		perror("sendmsg");

	printf("User pid %d send message\n", getpid());

	/* Read message from kernel */
	memset(nlh, 0, sizeof(nlh));
	recvmsg(sock_fd, &msg, 0);
	printf("User pid %d receive message: %s\n", getpid(), NLMSG_DATA(nlh));

	/* Read message from kernel */
	while (1) {
		memset(nlh, 0, sizeof(nlh));
		recvmsg(sock_fd, &msg, 0);
		printf("User pid %d receive message: %s\n", getpid(), NLMSG_DATA(nlh));
	}

	close(sock_fd);

	return 0;
}
