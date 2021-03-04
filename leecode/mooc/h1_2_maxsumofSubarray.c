#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int maxsumofSubarray(int *arr, int num)
{
    int thisSum = 0;
    int maxSum = 0;

    for (int i = 0; i < num; i++) {
        if (thisSum > 0)
            thisSum += arr[i];
        else
            thisSum = arr[i];
        maxSum = fmax(thisSum, maxSum);
    }

    return maxSum;
}

int main(void)
{
    int num;
    scanf("%d", &num);

    int *l = malloc(sizeof(int) * num);
    for (int i = 0; i < num; i++) {
        scanf("%d", l + i);
    }

    printf("%d\n", maxsumofSubarray(l, num));
    free(l);
    return 0;
}
