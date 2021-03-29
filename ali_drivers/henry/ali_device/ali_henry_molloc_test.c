#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

int mem_alloc_page(void)
{
	struct page *p = NULL;
	void *vaddr;
	unsigned long paddr;

	p = alloc_page(GFP_KERNEL);
	if (!p)
		return -ENOMEM;

	printk("alloc_page:\n");
	printk("\tAddress of page:%p\n", p);

	vaddr = page_address(p);
	printk("\tAddress of page_address:%p\n", vaddr);

	paddr = virt_to_phys(vaddr);
	printk("\tAddress of virt_to_phys:%lx\n", paddr);

	put_page(p);

	return 0;
}

int mem_kmalloc(void)
{
	void *k = NULL;
	unsigned long paddr;

	k = kmalloc(100, GFP_KERNEL);
	if (!k)
		return -ENOMEM;

	printk("kmalloc:\n");
	printk("\tAddress of kmalloc:%p\n", k);

	paddr = virt_to_phys(k);
	printk("\tAddress of virt_to_phys:%lx\n", paddr);

	kfree(k);

	return 0;
}

int mem_vmalloc(void)
{
	void *vk = NULL;
	unsigned long paddr;
	void *k;
	struct vm_struct *vm = NULL;
	int i;

	vk = vmalloc(8 * 1024);
	if (!vk)
		return -ENOMEM;

	memset(vk, 5, 8*1024);

	printk("vmalloc:\n");
	printk("\tAddress of vmalloc:%p\n", vk);

	paddr = virt_to_phys(vk);
	printk("\tAddress of virt_to_phys:%lx(NOT CORRECT!!)\n", paddr);

	vm = find_vm_area(vk);
	if (!vm)
		return -EFAULT;

	printk("\tvm info of vk[%p]: vm->addr[%p], vm->nr_pages[%d]\n",
		vk,	vm->addr, vm->nr_pages);

	for (i = 0; i < vm->nr_pages; i++) {
		k = page_address(vm->pages[i]);

		printk("\tpage[%d]:%p, vaddr[%p], paddr[%lx]\n",
			i, vm->pages[i], k, virt_to_phys(k));
	}

	vfree(vk);
	return 0;
}
