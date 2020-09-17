#include <linux/netlink.h>
#include <poll.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void die(char *s)
{
	write(2, s, strlen(s));
	exit(1);
}

int main(int argc, char *argv[])
{
	struct sockaddr_nl nls;
	struct pollfd pfd;
	char buf[512];

	/* open hotplug event netlink socket */
	memset(&nls, 0, sizeof(struct sockaddr_nl));
	nls.nl_family = AF_NETLINK;
	nls.nl_pid = getpid();
	nls.nl_groups = -1;

	pfd.events = POLLIN;
	pfd.fd = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);
	if (pfd.fd == -1)
		die("Not root\n");

	/* listen to netlink socket */
	if (bind(pfd.fd, (void *)&nls, sizeof(struct sockaddr_nl)))
		die("Bind failed\n");

	while (poll(&pfd, 1, -1) != -1) {
		memset(buf, 0, sizeof(buf));
		int len = recv(pfd.fd, buf, sizeof(buf)-1, MSG_DONTWAIT);
		if (len == -1)
			die("recv\n");

		/* print the data to stdout */
		printf("%s\n", buf);
	}
	die("poll\n");

	return 0;
}
