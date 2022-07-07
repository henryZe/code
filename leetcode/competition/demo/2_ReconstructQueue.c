#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

int compare(const void *data1, const void *data2)
{
    const int *child1 = *(int **)data1;
    const int *child2 = *(int **)data2;

    if (child1[0] == child2[0])
        return child2[1] - child1[1];

    return child1[0] - child2[0];
}

int **fill_space(int **ret, int peopleSize)
{
    int **space = malloc(sizeof(int *) * peopleSize);
    for (int i = 0; i < peopleSize; i++)
        space[i] = NULL;

    int count;
    for (int i = 0; i < peopleSize; i++) {
        count = ret[i][1] + 1;

        for (int j = 0; j < peopleSize; j++) {
            if (!space[j]) {
                count--;
                if (!count) {
                    space[j] = ret[i];
                    break;
                }
            }
        }
    }

    return space;
}

int **ReconstructQueue(int **people, int peopleSize, int *peopleColSize,
                        int *returnSize, int **returnColumnSizes)
{
    int i;

    *returnSize = peopleSize;

    int *ColumnSizes = malloc(sizeof(int) * peopleSize);
    *returnColumnSizes = ColumnSizes;
    for (i = 0; i < peopleSize; i++) {
        ColumnSizes[i] = peopleColSize[i];
    }

    int **ret = malloc(sizeof(int *) * peopleSize);
    for (i = 0; i < peopleSize; i++) {
        ret[i] = malloc(sizeof(int) * 2);
        ret[i][0] = people[i][0];
        ret[i][1] = people[i][1];
    }

    qsort(ret, peopleSize, sizeof(int *), compare);
    return fill_space(ret, peopleSize);
}

void dump(int **data, int size)
{
    for (int i = 0; i < size; i++) {
        printf("[%d,%d],", data[i][0], data[i][1]);
    }
    printf("\n");
}

int main(void)
{
    int data0[] = {8,0};
    int data1[] = {4,4};
    int data2[] = {8,1};
    int data3[] = {5,0};
    int data4[] = {6,1};
    int data5[] = {5,2};
    int *data[] = { data0, data1, data2, data3, data4, data5 };
    int size_arr[] = {2, 2, 2, 2, 2, 2};
    int size = 6;

    // int size = 2000;
    // int **data = malloc(sizeof(int *) * size);
    // int *size_arr = malloc(sizeof(int) * size);
    // for (int i = 0; i < size; i++) {
    //     data[i] = malloc(sizeof(int) * 2);
    //     data[i][0] = random() % 100;
    //     size_arr[i] = 2;
    // }

    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < i; j++) {
            if (data[j][0] >= data[i][0]) {
                count++;
            }
        }
        data[i][1] = count;
    }

    int returnSize;
    int *returnColumnSizes;
    int **data_out;

    data_out = ReconstructQueue(data, size, size_arr,
                                &returnSize, &returnColumnSizes);
    dump(data_out, size);

    return 0;
}
