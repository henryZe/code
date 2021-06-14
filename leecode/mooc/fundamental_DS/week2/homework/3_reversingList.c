#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int index;
    int data;
    int next_index;
};

int main(void)
{
    int start_index, node_num, reverse_num;
    int index, data, next_index;
    struct node *raw_list;

    scanf("%d %d %d", &start_index, &node_num, &reverse_num);

    raw_list = malloc(sizeof(struct node) * 100001);

    for (int i = 0; i < node_num; i++) {
        scanf("%d %d %d", &index, &data, &next_index);

        raw_list[index].index = index;
        raw_list[index].data = data;
        raw_list[index].next_index = next_index;
    }

    int dest = start_index;
    int count = 0;
    while (dest != -1) {
        dest = raw_list[dest].next_index;
        count++;
    }
    node_num = count;

    raw_list[100000].index = 100000;
    raw_list[100000].next_index = start_index;
    int pre = 100000;
    int cur = raw_list[pre].next_index;

    for (int i = reverse_num; i <= node_num; i += reverse_num) {
        int next = raw_list[cur].next_index;

        for (int j = 0; j < (reverse_num - 1); j++) {
            raw_list[cur].next_index = raw_list[next].next_index;
            // printf("cur->next %d\n", raw_list[raw_list[cur].next_index].data);

            raw_list[next].next_index = raw_list[pre].next_index;
            // printf("next->next %d\n", raw_list[raw_list[next].next_index].data);

            raw_list[pre].next_index = raw_list[next].index;
            // printf("pre->next %d\n", raw_list[raw_list[pre].next_index].data);

            next = raw_list[cur].next_index;
            // printf("next %d\n", raw_list[next].data);
        }

        pre = raw_list[cur].index;
        // printf("i pre %d\n", raw_list[pre].data);
        cur = raw_list[next].index;
        // printf("i cur %d\n", raw_list[cur].data);
    }

    // printf("\n");
    int it;
    for (it = raw_list[100000].next_index; raw_list[it].next_index != -1; it = raw_list[it].next_index) {
        printf("%05d %d %05d\n", raw_list[it].index, raw_list[it].data, raw_list[it].next_index);
    }
    printf("%05d %d %d\n", raw_list[it].index, raw_list[it].data, raw_list[it].next_index);

    free(raw_list);
    return 0;
}