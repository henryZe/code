#include <stdlib.h>

int **p;

int compare(const void *a1, const void *a2)
{
    int a = *(int *)a1;
    int b = *(int *)a2;

    if (p[a][1] > p[b][1])
        return 1;

    return -1;
}

int findMinArrowShots(int** points, int pointsSize, int* pointsColSize)
{
    int i;
    int idx[pointsSize];

    for (i = 0; i < pointsSize; i++) {
        idx[i] = i;
    }

    p = points;
    qsort(idx, pointsSize, sizeof(int), compare);

    int arrow = points[idx[0]][1];
    int res = 1;

    for (i = 1; i < pointsSize; i++) {
        if (points[idx[i]][0] <= arrow &&
            arrow <= points[idx[i]][1]) {
            continue;
        }

        arrow = points[idx[i]][1];
        res++;
    }

    return res;
}
