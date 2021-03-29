#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "page.h"

#define DEBUG 0

#define ALLOC_TIMES_PER_THREAD 20
#define CREATE_THREAD_TIMES 20

void *test_app(void *data)
{
	struct page *pp[ALLOC_TIMES_PER_THREAD] = {NULL};
	unsigned char order[ALLOC_TIMES_PER_THREAD] = {0};
	int i;

#if DEBUG
	size_t calc;
	size_t suppose_napges = npages;
#endif

	//sleep(1);

	for (i = 0; i < ALLOC_TIMES_PER_THREAD; i++)
		order[i] = random() % MAX_ORDER;

	for (i = 0; i < ALLOC_TIMES_PER_THREAD; i++) {
		pp[i] = pages_alloc(0, order[i]);

#if DEBUG
		suppose_napges -= (1 << order[i]);
		calc = show_mem(DEBUG, 1, 1);
		if (calc != suppose_napges) {
			printf("Error: alloc should: %ld pages\n", suppose_napges);
			return NULL;
		}
#endif
		//sleep(1);
	}

	//sleep(1);

	for (i = 0; i < ALLOC_TIMES_PER_THREAD; i++) {
		if (pp[i]) {			
			pages_free(pp[i]);

#if DEBUG
			suppose_napges += (1 << order[i]);
			calc = show_mem(DEBUG, 1, 1);
			if (calc != suppose_napges) {
				printf("Error: free should: %ld pages order %d\n", suppose_napges, order[i]);
				return NULL;
			}
#endif
		}
	}

	return NULL;
}

int main(int argc, char **argv)
{
	pthread_t tid[CREATE_THREAD_TIMES];
	int i;

	srandom(time(NULL));

	if (argc != 2)
		mem_init(32000);
	else
		mem_init(atoi(argv[1]));

	show_mem(DEBUG, 1, 1);

	for (i = 0; i < CREATE_THREAD_TIMES; i++)
		pthread_create(tid + i, NULL, test_app, NULL);

	for (i = 0; i < CREATE_THREAD_TIMES; i++)
		pthread_join(tid[i], NULL);

	show_mem(1, 1, 0);

	return 0;
}
