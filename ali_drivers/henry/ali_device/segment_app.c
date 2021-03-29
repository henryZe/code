#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>

int bss_var;

int proc_mem(void)
{
	printf("below are addresses of types of process's mem\n");
	printf("Text location:\n");
	printf("\tAddress of main(Code Segment):%p\n", proc_mem);
	printf("____________________________\n");

	int stack_var0 = 2;
	printf("Stack Location:\n");
	printf("\tInitial end of stack:%p\n", &stack_var0);
	int stack_var1 = 3;
	printf("\tnew end of stack:%p\n", &stack_var1);
	printf("____________________________\n");

	static int data_var0 = 1;
	printf("Data Location:\n");
	printf("\tAddress of data_var(Data Segment):%p\n", &data_var0);
	static int data_var1 = 4;
	printf("\tNew end of data_var(Data Segment):%p\n", &data_var1);
	printf("____________________________\n");

	printf("BSS Location:\n");
	printf("\tAddress of bss_var:%p\n", &bss_var);
	printf("____________________________\n");

	char *b = sbrk((ptrdiff_t)0);
	printf("Heap Location:\n");
	printf("\tInitial end of heap:%p\n", b);

	brk(b + 4);
	b = sbrk((ptrdiff_t)0);
	printf("\tNew end of heap:%p\n", b);

	char *buffer;
	buffer = (char *)malloc(1<<10);
	printf("1KB buffer %p\n", buffer);
	free(buffer);

	buffer = (char *)malloc(1<<20);
	printf("1MB buffer %p\n", buffer);
	free(buffer);

	return 0;
}

int max_alloc(void)
{
	int MB = 0;
	char *buffer;

	for (buffer = (char *)malloc(1<<20); buffer; buffer = (char *)malloc(1<<20)) {
		memset(buffer, 0x5a, (1<<20));
		++MB;
	}

	printf("\nMaximun allocated %d MB\n", MB);
	return 0;
}

int main()
{
	proc_mem();
	max_alloc();

	return 0;
}
