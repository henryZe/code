#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))

int **res;
int size;
int *columnSize;
int *index_arr;

int g_target;
int *g_num;
int g_numLen;

int time = 0;

void display(int *cur, int len)
{
    time++;
    printf("%d cur:[", time);
    for (int i = 0; i < len; i++)
        printf("%d, ", cur[i]);
    printf("]\n");
}

void dfs(int sel, int *cur, int len, int cur_sum)
{
    // display(cur, len);

    if (cur_sum == g_target) {
        int *temp = (int *)malloc(sizeof(int) * len);
        for (int i = 0; i < len; i++)
            temp[i] = cur[i];
        res[size] = temp;
        columnSize[size] = len;
        size++;
        return;
    }

    for (int i = sel; i < g_numLen; i++) {
        if (g_num[index_arr[i]] == -1)
            // already occupied
            continue;

        if ((g_num[index_arr[i]] + cur_sum) <= g_target) {
            cur[len] = g_num[index_arr[i]];
            // means occupied
            g_num[index_arr[i]] = -1;
            dfs(i + 1, cur, len + 1, cur_sum + cur[len]);
            g_num[index_arr[i]] = cur[len];
        } else {
            break;
        }

        // remove dup result
        while ((i + 1 < g_numLen) && (g_num[index_arr[i]] == g_num[index_arr[i + 1]])) {
            i++;
        }
    }
    return;
}

int compare(const void *a, const void *b)
{
    return g_num[*(int *)a] - g_num[*(int *)b];
}

int** combinationSum2(int* num, int numLen, int target, int* returnSize, int** returnColumnSizes)
{
    g_target = target;
    g_num = num;
    g_numLen = numLen;

    index_arr = (int *)malloc(numLen * sizeof(int));
    for (int i = 0; i < numLen; i++)
        index_arr[i] = i;

    qsort(index_arr, numLen, sizeof(int), compare);

    int *cur = (int *)malloc(sizeof(int) * numLen);
    size = 0;
    columnSize = (int *)malloc(sizeof(int) * numLen);
    res = (int **)malloc(numLen * sizeof(int *));

    dfs(0, cur, 0, 0);

    *returnSize = size;
    *returnColumnSizes = columnSize;
    return res;
}

int main(void)
{
    int num[] = {100,10,20,70,60,10,50};
    int n = ARRAYSIZE(num);
    int t = 80;

    int returnSize;
    int *returnColumnSizes;
    int** res = combinationSum2(num, n, t, &returnSize, &returnColumnSizes);

    printf("[");
    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d,", res[i][j]);
        }
        printf("],");
    }
    printf("]\n");

    return 0;
}