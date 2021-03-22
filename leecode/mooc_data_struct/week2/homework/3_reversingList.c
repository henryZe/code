#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int index;
    int data;
    int next_index;
    struct node *next;
};

// list_link()
// {

// }

int main(void)
{
    int start_index, node_num, reverse_num;
    struct node dummy_node;
    struct node *node_list;

    scanf("%d %d %d", &start_index, &node_num, &reverse_num);
    dummy_node.next_index = start_index;
    dummy_node.next = NULL;

    node_list = malloc(sizeof(struct node) * node_num);
    for (int i = 0; i < node_num; i++) {
        scanf("%d %d %d", &node_list[i].index,
                          &node_list[i].data,
                          &node_list[i].next_index);
        node_list[i].next = NULL;
    }

    struct node *head = &dummy_node;
    while (head) {
        for (int k = 0; k < node_num; k++) {
            if (head->next_index == -1) {
                head->next = NULL;
                break;
            }
            if (head->next_index == node_list[k].index) {
                head->next = &(node_list[k]);
                break;
            }
        }
        head = head->next;
    }

    // struct node *pre = &dummy_node;
    // struct node *cur = pre->next;
    // struct node *next = cur->next;

    // if (node_num >= reverse_num) {
    //     for (int i = 0; i < node_num; i += reverse_num) {
    //         for (int j = 0; j < reverse_num; j++) {
    //             cur->next = next->next;
    //             cur->next_index = next->next_index;

    //             next->next = pre->next;
    //             next->next_index = pre->next_index;

    //             pre->next = next;
    //             pre->next_index = next->index;

    //             next = cur->next;
    //         }
    //     }
    // }

    printf("\n");
    for (struct node *it = dummy_node.next; it; it = it->next) {
        if (it->next_index != -1)
            printf("%05d %d %05d\n", it->index, it->data, it->next_index);
        else
            printf("%05d %d %d\n", it->index, it->data, it->next_index);
    }

    free(node_list);
    return 0;
}