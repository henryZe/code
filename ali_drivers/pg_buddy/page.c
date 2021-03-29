#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

#include "page.h"

#define debug(...) //printf
static int no_mem_times;
static unsigned long free_num;

#define PGSHIFT 12
#define PGSIZE (1 << PGSHIFT)
#define PTXSHIFT	12								/* offset of PTX in a linear address */

#define KERNBASE 0
#define KADDR(pa) kaddr(__FILE__, __LINE__, pa)

#define PGNUM(la)	(((unsigned long) (la)) >> PTXSHIFT)

#define min(x, y) ((x < y)? x : y)

struct list_head page_free_list[MAX_ORDER];	/* Recent Free head of physical pages, atomic */
//static unsigned int *page_free_map[MAX_ORDER];		/* Free map of physical pages, atomic */
static pthread_mutex_t mutex;

static inline void *
kaddr(const char *file, int line, unsigned long pa)
{
	if (PGNUM(pa) >= npages)
		printf("%s %d: KADDR called with invalid pa %08lx\n", file, line, pa);
	return (void *)(pa + KERNBASE);
}

static inline unsigned long	// physaddr_t
page2pa(struct page *pp)
{
	return (pp - pages) << PGSHIFT;
}

static inline void *
page2kva(struct page *pp)
{
	return KADDR(page2pa(pp));
}

struct page *
page_find_buddy(struct page *page, unsigned char order)
{
	unsigned long page_idx = page - pages;
    unsigned long buddy_idx = page_idx ^ (1 << order);
	struct page *pp = page + buddy_idx - page_idx;

	if ((pp < pages) || (pp >= (pages + npages)))
		return NULL;

    return pp;
}

struct page *
search_page_from_list(struct page *pp, unsigned char order)
{
	struct page *target = NULL;

	list_for_each_entry(target, &page_free_list[order], pp_link) {	/* TODO */
		if (target == pp) {
			list_del(&pp->pp_link);
			return pp;
		}
	}

	return NULL;
}

int
page_init(void)
{
	int i;

	for (i = 0; i < npages; i++)
		pages_free(pages + i);

	return 0;
}

struct page *
divide_buddy(unsigned char order)
{
	struct page *buddy, *pp = NULL;

	if (!(order < MAX_ORDER) || (!order))
		return NULL;

	pp = list_first_entry_or_null(&page_free_list[order], struct page, pp_link);
	if (!pp) {
		pp = divide_buddy(order + 1);
		if (!pp)
			return NULL;

	} else {
		list_del(&pp->pp_link);
	}

	buddy = page_find_buddy(pp, order - 1);
	if (buddy) {
		debug("divide %ld\n", buddy - pages);
		list_add(&buddy->pp_link, &page_free_list[order - 1]);
	}

	return pp;
}

int
merge_buddy(struct page *pp, unsigned char order)
{
	unsigned char i;
	struct page *buddy = NULL;

	for (i = order; i < (MAX_ORDER - 1); i++) {
		buddy = page_find_buddy(pp, i);
		if (!buddy)
			break;

		debug("[page] delete %ld order %d\n", buddy - pages, i);
		buddy = search_page_from_list(buddy, i);
		if (!buddy)
			break;

		debug("[page] buddy %ld order %d\n", buddy - pages, i);
		pp = min(buddy, pp);
	}

	debug("[page] insert %ld order %d\n", pp - pages, i);
	list_add(&pp->pp_link, &page_free_list[i]);

	return 0;
}

struct page *
pages_alloc(int flags, unsigned char order)
{
	struct page *pp = NULL;

	if (!(order < MAX_ORDER))
		return NULL;

	debug("alloc order %d\n", order);

	pthread_mutex_lock(&mutex);

	pp = list_first_entry_or_null(&page_free_list[order], struct page, pp_link);
	if (pp) {
		list_del(&pp->pp_link);

	} else {
		pp = divide_buddy(order + 1);
		if (!pp) {
			printf("\nno memory %dth, left: %ld, request: %d!!!!!!!!!!!!!\n",
				++no_mem_times, free_num, 1 << order);
			show_mem(1, 0, 1);

			pthread_mutex_unlock(&mutex);
			goto out;
		}
	}
	pp->order = order;

	free_num -= (1 << order);

	pthread_mutex_unlock(&mutex);

	if (flags & ALLOC_ZERO)
		memset(page2kva(pp), 0, PGSIZE * (1 << order));

out:
	return pp;
}

struct page *
page_alloc(void)
{
	return pages_alloc(ALLOC_ZERO, 0);
}

void
pages_free(struct page *pp)			/* must be the pages head */
{
	debug("free %ld order %d\n", pp - pages, pp->order);

	if (!pp->pp_ref && !pp->pp_link.prev) {

		pthread_mutex_lock(&mutex);

		merge_buddy(pp, pp->order);
		free_num += (1 << pp->order);
		pp->order = INVALID_ORDER;

		pthread_mutex_unlock(&mutex);

	} else if (pp->pp_ref) {
		printf("Busy page\n");

	} else {
		/* pp->pp_link is already in list */
		printf("Free twice\n");
	}
}

int get_pages(struct page *pp)
{
	pp->pp_ref++;		/* atomic */
	return 0;
}

int put_pages(struct page *pp)
{
	pp->pp_ref--;		/* atomic */
	if (!(pp->pp_ref))
		pages_free(pp);

	return 0;
}

int
mem_init(unsigned long size)
{
	int i;

	npages = size;			/* unit: 4KB */
	for (i = 0; i < MAX_ORDER; i++)
		INIT_LIST_HEAD(&page_free_list[i]);
	pages = (struct page *)malloc(sizeof(struct page) * npages);
	memset(pages, 0, (sizeof(struct page) * npages));

	printf("total %ld pages, pages address: %p\n", size, pages);

	pthread_mutex_init(&mutex, NULL);

	page_init();

	return 0;
}

unsigned long
show_mem(int debug_flag, int lock, int print_ptr)
{
	int i, list_num;
	struct page *pp;
	unsigned long n_page = 0;

	if (lock)
		pthread_mutex_lock(&mutex);

	for (i = 0; i < MAX_ORDER; i++) {
		list_num = 0;
		list_for_each_entry(pp, &page_free_list[i], pp_link) {
			n_page += (1 << i);
			list_num++;
			if (debug_flag && print_ptr)
				printf("pp %ld\n", pp - pages);
		}

		if (debug_flag)
			printf("order: %02d num: %02d mem: %08x pages\n", i, list_num, list_num << i);
	}

	if (lock)
		pthread_mutex_unlock(&mutex);

	if (debug_flag)
		printf("left: %ld pages\n", n_page);

	return n_page;
}
