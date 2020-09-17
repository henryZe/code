#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "rbtree.h"

#define MAC_LENGTH 8
#define SUM_LIMIT 100

#define NODE_INSERT 0
#define NODE_UPDATE 1

static int sum;

struct tree_node {
	struct rb_node node;
	unsigned char mac_addr[MAC_LENGTH];
	time_t time_val;
};

int delete_oldest_node(struct rb_root *root)
{
	struct tree_node *node, *n_node, *min_node = NULL;

	rbtree_postorder_for_each_entry_safe(node, n_node, root, node) {
		if (min_node)
			min_node = (min_node->time_val < node->time_val)?
				min_node: node;
		else
			min_node = node;
	}

	printf("delete mac_addr: %d, time: %ld\n",
		min_node->mac_addr[0], min_node->time_val);
	rb_erase(&min_node->node, root);
	free(min_node);

	sum--;

	return 0;
}

int tree_insert(struct rb_root *root, struct tree_node *data)
{
	int result, op_count = 0;
	struct rb_node *parent = NULL;
	struct tree_node *this;
	struct rb_node **new = &(root->rb_node);

	while (*new) {
		this = rb_entry(*new, struct tree_node, node);

		result = strncmp(data->mac_addr, this->mac_addr, MAC_LENGTH);
		parent = *new;
		if (result < 0) {
			op_count++;
			printf("left %d\n", op_count);
			new = &(parent->rb_left);

		} else if (result > 0) {
			op_count++;
			printf("right %d\n", op_count);
			new = &(parent->rb_right);

		} else {
			printf("existed mac_addr: %d, time: %ld\n",
				this->mac_addr[0], data->time_val);
			this->time_val = data->time_val;

			return NODE_UPDATE;
		}
	}

	if (sum < SUM_LIMIT) {
		rb_link_node(&(data->node), parent, new);
		rb_insert_color(&(data->node), root);
		sum++;

	} else {
		delete_oldest_node(root);

		rb_link_node(&data->node, parent, new);
		rb_insert_color(&data->node, root);
		sum++;
	}

	return NODE_INSERT;
}

int display_tree(struct rb_root *root)
{
	struct tree_node *node = NULL, *n_node = NULL;

	rbtree_postorder_for_each_entry_safe(node, n_node, root, node)
		printf("display: mac %d\n", node->mac_addr[0]);

	return 0;
}

int main()
{
	int i, ret;
	struct tree_node *tree_node_p;
	struct rb_root tree = RB_ROOT;

	for (i = 0; i < (2 * SUM_LIMIT); i++) {
		tree_node_p = (struct tree_node *)malloc(sizeof(struct tree_node));
		memset(tree_node_p, 0, sizeof(*tree_node_p));

		tree_node_p->time_val = time(NULL);
		memset(tree_node_p->mac_addr, i, MAC_LENGTH);

		printf("insert mac_addr: %d, time: %ld\n",
			tree_node_p->mac_addr[0], tree_node_p->time_val);

		ret = tree_insert(&tree, tree_node_p);
		if (ret == NODE_UPDATE)
			free(tree_node_p);

		//sleep(1);
	}
	
	display_tree(&tree);

	return 0;
}
