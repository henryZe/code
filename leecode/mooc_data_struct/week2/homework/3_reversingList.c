#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int index;
    int data;
    int next_index;
    struct node *next;
};

list_link()
{

}

int main(void)
{
    int start_index, node_num, reverse_num;
    struct node dummy_node;
    struct node *node_list;

    scanf("%d %d %d", &start_index, &node_num, &reverse_num);
    dummy_node.next_index = start_index;

    node_list = malloc(sizeof(struct node) * node_num);
    for (int i = 0; i < node_num; i++) {
        scanf("%d %d %d", &node_list[i].index,
                &node_list[i].data, &node_list[i].next_index);
    }


    free(node_list);
    return 0;
}