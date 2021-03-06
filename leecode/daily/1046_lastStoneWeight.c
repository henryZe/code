#include <stdio.h>
#include <stdlib.h>

// 大顶堆

#define SIZE (30)

struct heapq {
    int heap[SIZE + 1];
    int heapSize;
    void(*push)(struct heapq *heap, int x);
    int(*pop)(struct heapq *heap);
    int(*top)(struct heapq *heap);
};

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// insert: O(logN)
void heappush(struct heapq *heap, int x)
{
    int *h = heap->heap;

    if (heap->heapSize == SIZE)
        return;

    h[++(heap->heapSize)] = x;

    for (int i = heap->heapSize; i > 1 && h[i] > h[i >> 1]; i >>= 1) {
        swap(&h[i], &h[i >> 1]);
    }
}

// search: O(logN)
int heappop(struct heapq *heap)
{
    int *h = heap->heap;
    int tmp = h[1];
    int i = 1, j = 2;

    if (!heap->heapSize) {
        return -1;
    }

    h[1] = h[heap->heapSize--];
    while (j <= heap->heapSize) {
        if (h[j + 1] > h[j])
            j++;

        if (h[i] < h[j]) {
            swap(&h[i], &h[j]);
            i = j;
            j <<= 1;
            continue;
        }

        break;
    }

    return tmp;
}

int heaptop(struct heapq *heap)
{
    return heap->heap[1];
}

struct heapq *heapify(int *list, int size)
{
    struct heapq *object = malloc(sizeof(struct heapq));
    object->heapSize = 0;
    object->push = heappush;
    object->pop = heappop;
    object->top = heaptop;

    for (int i = 0; i < size; i++) {
        object->push(object, list[i]);
    }

    return object;
}

int lastStoneWeight(int* stones, int stonesSize)
{
    struct heapq *obj = heapify(stones, stonesSize);
    int res, tmp1, tmp2;

    while (1) {
        tmp1 = obj->pop(obj);
        tmp2 = obj->pop(obj);

        if (tmp1 < 0) {
            res = 0;
            break;
        }
        if (tmp2 < 0) {
            res = tmp1;
            break;
        }

        if (tmp1 == tmp2) {
            continue;
        } else {
            obj->push(obj, tmp1 - tmp2);
        }
    }

    free(obj);
    return res;
}

int main(void)
{
    // int stonesSize = 6;
    // int stones[] = {2,7,4,1,8,1};
    int stonesSize = 1;
    int stones[] = {1};

    printf("%d\n", lastStoneWeight(stones, stonesSize));
    return 0;
}
