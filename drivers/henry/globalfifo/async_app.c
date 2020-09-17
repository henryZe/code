#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_LEN 20

void signalio_handler(int signum)
{
	printf("signalio_handler catch %d\n", signum);
}

int main()
{
	int flags, fd;

	fd = open("/dev/globalfifo", O_RDWR, S_IRUSR | S_IWUSR);
	if (fd != -1) {

		/* specify handler for signal */
		signal(SIGIO, signalio_handler);

		/* current process owns this fd */
		fcntl(fd, F_SETOWN, getpid());

		/* launch the async mechanism */
		flags = fcntl(STDIN_FILENO, F_GETFL);
		fcntl(fd, F_SETFL, flags | FASYNC);

		while(1);
	} else
		printf("device open failed\n");

}
