#include <stdio.h>

struct node {
    int num;
    int next_index;
};

int last_one(int num)
{
    struct node array[1000];

    for (int i = 0; i < num; i++) {
        array[i].num = i;
        array[i].next_index = (i + 1) % num;
    }

    int prev_index = 0, curr_index = 0;
    while (num > 1) {
        for (int i = 0; i < 2; i++) {
            prev_index = curr_index;
            curr_index = array[curr_index].next_index;
        }
        array[prev_index].next_index = array[curr_index].next_index;
        curr_index = array[curr_index].next_index;
        num--;
    }

    return array[curr_index].num;
}

int main(void)
{
    int num, ret;

    while (scanf("%d\n", &num) != EOF) {
        if (num > 1000) {
            num = 1000;
        }

        ret = last_one(num);
        printf("%d\n", ret);
    }

    return 0;
}