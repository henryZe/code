#ifndef PAGE_H
#define PAGE_H

#include "list.h"

#define MAX_ORDER 11
#define INVALID_ORDER (~0)

size_t npages;										/* Amount of physical memory (in pages) */
struct page *pages;									/* Physical page state array */

enum {
	/* For page_alloc, zero the returned physical page. */
	ALLOC_ZERO = 1<<0,
};

struct page {
	struct list_head pp_link;
	unsigned char pp_ref;	/* atomic */
	unsigned char order;	/* atomic */
};

int mem_init(unsigned long size);
unsigned long show_mem(int debug_flag, int lock, int print_ptr);
void pages_free(struct page *pp);			/* must be the pages head */
struct page *pages_alloc(int flags, unsigned char order);

#endif
