#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/kfifo.h>
#include <linux/idr.h>
#include <linux/slab.h>

#define NUM_NODES 32

struct kfifo fifo;
struct idr idr_huh;
struct ida ida_huh;
struct rb_root tree = RB_ROOT;

struct tree_node {
	struct rb_node node;
	char *string;
};

static int test_fifo_init(void)
{
	int ret;
	unsigned int i = 0, val;

	printk("test_fifo_init\n");

	ret = kfifo_alloc(&fifo, 16*4, GFP_KERNEL);
	if (ret) {
		printk("kfifo_alloc err\n");
		return ret;
	}

	printk("in:\n");
	while (kfifo_avail(&fifo)) {
		ret = kfifo_in(&fifo, &i, sizeof(i));
		if (ret != sizeof(i)) {
			printk("kfifo_in err\n");
			return -EINVAL;
		}

		printk("%u\n", i);

		i++;
	}

	ret = kfifo_out_peek(&fifo, &val, sizeof(val));
	if (ret != sizeof(val))	{
		printk("kfifo_out_peek err\n");
		return -EINVAL;
	}
	printk("peek: %u\n", val);

	printk("out:\n");
	while (kfifo_len(&fifo)) {
		ret = kfifo_out(&fifo, &val, sizeof(val));
		if (ret != sizeof(val)) {
			printk("kfifo_out err\n");
			return -EINVAL;
		}

		printk("%u\n", val);
	}

	return 0;
}

static int test_idr_init(void)
{
	int id;
	int something_int = 10;
	int *idr_entry;

	printk("test_idr_init\n");

	idr_init(&idr_huh);

#if 0
	do {
		if (!idr_pre_get(&idr_huh, GFP_KERNEL))
			return -ENOSPC;

		ret = idr_get_new(&idr_huh, &something_int, &id);
	} while (ret == -EAGAIN);
#else
	idr_preload(GFP_KERNEL);

	id = idr_alloc(&idr_huh, &something_int, 0, 0, 0);
	if (id < 0) {
		printk("idr_alloc err\n");
		return id;
	}

	idr_preload_end();
#endif

	idr_entry = idr_find(&idr_huh, id);
	if (!idr_entry)
		return -EINVAL;

	printk("id: %d, content: %d\n", id, *idr_entry);

	idr_remove(&idr_huh, id);

	return 0;
}

static int test_ida_init(void)
{
	int i, id[2];

	printk("test_ida_init\n");

	for (i = 0; i < ARRAY_SIZE(id); i++) {
		id[i] = ida_simple_get(&ida_huh, 0, 0, GFP_KERNEL);
		if (id[i] < 0) {
			if (id[i] == -ENOSPC)
				printk("start <= id < end is empty\n");
			else if (id[i] == -ENOMEM)
				printk("memory allocation fail\n");

			return id[i];
		}
	}

	for (i = 0; i < ARRAY_SIZE(id); i++)
		printk("id%d: %d\n", i, id[i]);

	for (i = 0; i < ARRAY_SIZE(id); i++)
		ida_simple_remove(&ida_huh, id[i]);

	return 0;
}

struct tree_node *tree_search(struct rb_root *root, char *string)
{
	int i = 0, result;
	struct tree_node *data;
	struct rb_node *node = root->rb_node;

	while (node) {
		data = rb_entry(node, struct tree_node, node);

		i++;
		printk("search cmp %dth times\n", i);
		result = strcmp(string, data->string);
		if (result < 0)
			node = node->rb_left;
		else if (result > 0)
			node = node->rb_right;
		else
			return data;
	}

	return NULL;
}

int tree_insert(struct rb_root *root, struct tree_node *data)
{
	int result;
	struct rb_node *parent;
	struct tree_node *this;
	struct rb_node **new = &(root->rb_node);

	while (*new) {
		this = rb_entry(*new, struct tree_node, node);

		result = strcmp(data->string, this->string);
		parent = *new;
		if (result < 0)
			new = &(parent->rb_left);
		else if (result > 0)
			new = &(parent->rb_right);
		else {
			printk("that is existed.\n");
			return -EINVAL;
		}
	}

	rb_link_node(&data->node, parent, new);
	rb_insert_color(&data->node, root);

	return 0;
}

void tree_free(struct tree_node *data)
{
	kfree(data->string);
	data->string = NULL;
	kfree(data);
	data = NULL;
}

static int test_tree_init(void)
{
	int i, ret;
	char data_string[8];
	struct rb_node *node;
	struct tree_node *data;
	struct tree_node *tree_nodes[NUM_NODES];

	/* insert nodes */
	for (i = 0; i < NUM_NODES; i++) {
		tree_nodes[i] = kmalloc(sizeof(struct tree_node), GFP_KERNEL);
		tree_nodes[i]->string = kmalloc(8, GFP_KERNEL);

		sprintf(tree_nodes[i]->string, "henry%d", i);
		ret = tree_insert(&tree, tree_nodes[i]);
		if (ret)
			return -1;
	}


	/* travel nodes */
	printk("search all nodes:\n");
	for (node = rb_first(&tree); node; node = rb_next(node))
		printk("string: %s\n", rb_entry(node, struct tree_node, node)->string);

	/* search node */
	sprintf(data_string, "henry%d", NUM_NODES);
	printk("search node %s\n", data_string);
	data = tree_search(&tree, data_string);
	if (!data)
		printk("no %s\n", data_string);

	for (i = 1, node = rb_first(&tree); node; node = rb_next(node), i++) {
		printk("travel cmp %dth times\n", i);
		strcmp(rb_entry(node, struct tree_node, node)->string, data_string);
	}
	if (!node)
		printk("no %s\n", data_string);


	/* delete node */
	sprintf(data_string, "henry20");
	printk("delete node %s\n", data_string);
	data = tree_search(&tree, data_string);
	if (data) {
		rb_erase(&data->node, &tree);
		tree_free(data);
	} else
		printk("no %s\n", data_string);

	/* travel nodes */
	printk("search all nodes:\n");
	for (node = rb_first(&tree); node; node = rb_next(node))
		printk("string: %s\n", rb_entry(node, struct tree_node, node)->string);

	return 0;
}

static int __init kernel_data_struct_init(void)
{
	int ret;

	ret = test_fifo_init();
	if (ret)
		return ret;

	ret = test_idr_init();
	if (ret)
		return ret;

	ret = test_ida_init();
	if (ret)
		return ret;

	ret = test_tree_init();
	if (ret)
		return ret;

	return 0;
}
module_init(kernel_data_struct_init);

static void test_fifo_exit(void)
{
	printk("test_fifo_exit\n");

	kfifo_free(&fifo);
}

static void test_idr_exit(void)
{
	printk("test_idr_exit\n");

#if 0
	idr_remove_all(&idr_huh);
#endif

	idr_destroy(&idr_huh);
}

static void test_ida_exit(void)
{
	printk("test_ida_exit\n");
	ida_destroy(&ida_huh);
}

static void test_tree_exit(void)
{
	struct rb_node *node, *n_node;
	struct tree_node *data;

	printk("test_tree_exit\n");

	for (node = rb_first(&tree); node; node = n_node) {
		n_node = rb_next(node);
		data = rb_entry(node, struct tree_node, node);

		rb_erase(node, &tree);
		tree_free(data);
	}
}

static void __exit kernel_data_struct_exit(void)
{
	test_fifo_exit();
	test_idr_exit();
	test_ida_exit();
	test_tree_exit();
}
module_exit(kernel_data_struct_exit);

MODULE_AUTHOR("henry.zeng");
MODULE_DESCRIPTION("kernel data struct example");
MODULE_LICENSE("GPL v2");
MODULE_VERSION("1.0.0");
