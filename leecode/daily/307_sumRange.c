#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *tree;
    int len;
} NumArray;

int lowbit(int x)
{
    return x & (-x);
}

void update(NumArray *obj, int index, int delta)
{
    while (index <= obj->len) {
        obj->tree[index] += delta;
        // parent index
        index += lowbit(index);
    }
}

// prefix_sum = sum(arr[0:index])
int query(NumArray *obj, int index)
{
    int sum = 0;
    while (index > 0) {
        sum += obj->tree[index];
        index -= lowbit(index);
    }
    return sum;
}

void numArrayUpdate(NumArray* obj, int index, int val)
{
    int origin = query(obj, index + 1) - query(obj, index);
    update(obj, index, val - origin);
}

NumArray* numArrayCreate(int* nums, int numsSize)
{
    NumArray *obj = malloc(sizeof(NumArray));

    obj->tree = malloc(sizeof(int) * (numsSize + 1));
    memset(obj->tree, 0, sizeof(int) * (numsSize + 1));
    obj->len = numsSize;

    for (int i = 1; i <= obj->len; i++) {
        update(obj, i, nums[i - 1]);
    }

    return obj;
}

int numArraySumRange(NumArray* obj, int i, int j)
{
    return query(obj, j + 1) - query(obj, i);
}

void numArrayFree(NumArray* obj)
{
    free(obj->tree);
    free(obj);
}

int main(void)
{
    int arr[10] = {1, 3, 5};

    NumArray *tree = numArrayCreate(arr, 3);
    printf("sum(arr[0:2]) = %d\n", numArraySumRange(tree, 0, 2));
    numArrayUpdate(tree, 1, 2);
    printf("sum(arr[0:2]) = %d\n", numArraySumRange(tree, 0, 2));
    numArrayFree(tree);

    return 0;
}
