#include <stdlib.h>
#include <stdio.h>

struct Interval {
    int start;
    int end;
};

int compare(const void *a1, const void *a2)
{
    struct Interval *a = (struct Interval *)a1;
    struct Interval *b = (struct Interval *)a2;

    if (a->start == b->start) {
        return a->end - b->end;
    }

    return a->start - b->start;
}

void merge_two(struct Interval* cur, struct Interval* a)
{
    cur->end = cur->end > a->end ? cur->end : a->end;
}

struct Interval* merge(struct Interval* intervals, int intervalsLen, int* returnSize)
{
    if (!intervalsLen) {
        *returnSize = 0;
        return NULL;
    }

    qsort(intervals, intervalsLen, sizeof(struct Interval), compare);

    struct Interval* ret = (struct Interval*)malloc(intervalsLen * sizeof(struct Interval));
    *returnSize = 0;
    struct Interval cur = intervals[0];

    for (int i = 1; i < intervalsLen; i++) {
        struct Interval *a = intervals + i;
        if (cur.start <= a->start && a->start <= cur.end) {
            merge_two(&cur, a);
        } else {
            ret[*returnSize] = cur;
            (*returnSize)++;
            cur = *a;
        }
    }

    ret[*returnSize] = cur;
    (*returnSize)++;

    return ret;
}

int main(void)
{
    struct Interval intervals[] = {
        [0] = {
            .start = 10,
            .end = 30,
        },
        [1] = {
            .start = 20,
            .end = 60,
        },
        [2] = {
            .start = 80,
            .end = 100,
        },
        [3] = {
            .start = 150,
            .end = 180,
        },
    };
    int size;
    struct Interval *ret = merge(intervals, 4, &size);

    printf("[");
    for (int i = 0; i < size; i++) {
        printf("[%d,%d],", ret[i].start, ret[i].end);
    }
    printf("]\n");

    return 0;
}