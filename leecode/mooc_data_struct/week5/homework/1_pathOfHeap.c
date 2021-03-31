#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

struct heap {
    int *data;
    int capacity;
    int size;
};

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

bool IsFull(struct heap *h)
{
    return h->capacity == h->size;
}

bool IsEmpty(struct heap *h)
{
    return h->size == 0;
}

int Insert(struct heap *h, int x)
{
    int *d = h->data;

    if (IsFull(h))
        return -1;

    d[++(h->size)] = x;

    for (int i = h->size; d[i] < d[i >> 1]; i >>= 1) {
        swap(&d[i], &d[i >> 1]);
    }

    return 0;
}

int Delete(struct heap *h)
{
    int *d = h->data;
    int min = d[1];

    if (IsEmpty(h)) {
        return -1;
    }

    d[1] = d[h->size--];

    int parent, child;
    for (parent = 1, child = parent << 1; child <= h->size; parent = child) {
        if (child < h->size) {
            if (d[child] > d[child + 1]) {
                child++;
            }
        }

        if (d[child] >= d[parent]) {
            break;
        } 

        swap(d + child, d + parent);
        child <<= 1;
    }

    return min;
}

struct heap *create_heap(int num)
{
    struct heap *h = malloc(sizeof(struct heap));

    h->data = malloc(sizeof(int) * (num + 1));
    h->capacity = num;
    h->size = 0;

    // 小顶堆，[0] 作为 guardian
    h->data[0] = INT_MIN;
    for (int i = 1; i <= num; i++) {
        int val;
        scanf("%d", &val);
        Insert(h, val);
    }

    // printf("heap: ");
    // for (int i = 1; i <= num; i++) {
    //     printf("%d ", h->data[i]);
    // }
    // printf("\n");

    return h;
}

void printPath(struct heap *h, int index)
{
    for (int i = index; i; i >>= 1) {
        if (i > 1)
            printf("%d ", h->data[i]);
        else
            printf("%d\n", h->data[i]);
    }
}

int main(void)
{
    int num, numPath;
    scanf("%d %d", &num, &numPath);

    struct heap *h = create_heap(num);

    for (int i = 0; i < numPath; i++) {
        int index;
        scanf("%d", &index);
        printPath(h, index);
    }

    return 0;
}