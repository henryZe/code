#include <stdio.h>
#include <stdlib.h>

int maxSubsequenceSum(int *arr, int num)
{
    int cur_start;
    int thisSum = -1;
    int maxSum = -1;
    int start = 0, end = num - 1;

    for (int i = 0; i < num; i++) {
        if (thisSum >= 0) {
            thisSum += arr[i];
        } else {
            thisSum = arr[i];
            cur_start = i;
        }
        if (thisSum > maxSum) {
            maxSum = thisSum;
            start = cur_start;
            end = i;
        }
    }

    printf("%d %d %d\n", (maxSum > 0) ? maxSum : 0, arr[start], arr[end]);
    return 0;
}

int main(void)
{
    int num;
    scanf("%d", &num);

    int *l = malloc(sizeof(int) * num);
    for (int i = 0; i < num; i++) {
        scanf("%d", l + i);
    }

    maxSubsequenceSum(l, num);
    free(l);
    return 0;
}
