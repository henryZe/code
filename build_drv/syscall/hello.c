#include <linux/unistd.h>
#include <stdio.h>

int main(void)
{
	printf("api teset\n");
	syscall(366);
	return 0;
}
