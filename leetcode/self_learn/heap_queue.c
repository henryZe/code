#include <stdio.h>
#include <stdlib.h>

// 小顶堆

#define SIZE (1000)

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

    for (int i = heap->heapSize; i > 1 && h[i] < h[i >> 1]; i >>= 1) {
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
        if (h[j + 1] < h[j])
            j++;

        if (h[i] > h[j]) {
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

void siftDown(int *array, int parent, int size)
{
    while (parent << 1 <= size) {
        int child = parent << 1;    // left son
        if (child + 1 <= size && array[child] > array[child + 1]) {
            child++;                // right son
        }
        if (array[child] >= array[parent]) {
            break;
        }
        swap(&array[child], &array[parent]);

        parent = child;
    }
}

struct heapq *heapify(int *list, int size)
{
    struct heapq *object = malloc(sizeof(struct heapq));
    object->heapSize = 0;
    object->push = heappush;
    object->pop = heappop;
    object->top = heaptop;

    object->heapSize = size;
    for (int i = 0; i < size; i++)
        object->heap[i + 1] = list[i];

    // heapify: O(n)
    for (int i = (size >> 1); i > 0; i--)
        siftDown(object->heap, i, size);

    return object;
}

int main(void)
{
    int size = 11;
    int data[] = { 4, 981, 10, -17, 0, -20, 29, 50, 8, 43, -5 };
    struct heapq *obj = heapify(data, size);

    for (int i = 1; i < size + 1; i++) {
        printf("%d, ", obj->heap[i]);
    }
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf("%d, ", obj->pop(obj));
    }
    printf("\n");

    free(obj);
    return 0;
}
