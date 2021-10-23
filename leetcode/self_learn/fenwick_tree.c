#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

struct fenwick_tree {
    int *tree;
    int len;
};

int lowbit(int x)
{
    return x & (-x);
}

void update(struct fenwick_tree *obj, int index, int delta)
{
    while (index <= obj->len) {
        obj->tree[index] += delta;
        // parent index
        index += lowbit(index);
    }
}

// prefix_sum = sum(arr[0:index])
int query(struct fenwick_tree *obj, int index)
{
    int sum = 0;
    while (index > 0) {
        sum += obj->tree[index];
        index -= lowbit(index);
    }
    return sum;
}

struct fenwick_tree *fenwickTree(int *arr, int size)
{
    struct fenwick_tree *obj = malloc(sizeof(struct fenwick_tree));
    
    obj->tree = malloc(sizeof(int) * (size + 1));
    obj->tree[0] = 0;
    obj->len = size;

    for (int i = 1; i <= obj->len; i++) {
        update(obj, i, arr[i - 1]);
    }

    return obj;
}

int main(void)
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    struct fenwick_tree *tree = fenwickTree(arr, 10);

    printf("sum(arr[0:5]) = %d\n", query(tree, 5));
    printf("sum(arr[0:10]) = %d\n", query(tree, 10));
    printf("sum(arr[0:6]) = %d\n", query(tree, 6));

    return 0;
}
