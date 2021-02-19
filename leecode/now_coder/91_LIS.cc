#include "math.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int* LIS(int* arr, int arrLen, int* returnSize ) {
    // write code here
    if (!arrLen)
        return 0;

    int dp[arrLen];
    for (int i = 0; i < arrLen; i++) {
        dp[i] = 1;
    }

    for (int i = 0; i < arrLen; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j]) {
                dp[i] = fmax(dp[i], dp[j] + 1);
            }
        }
    }

    int maxi = 0;
    for (int i = 0; i < arrLen; i++) {
        if (dp[i] > dp[maxi])
            maxi = i;
    }

    int *newarr = (int *)malloc(sizeof(int) * arrLen);
    *returnSize = dp[maxi];
    int num = 0;
    for (int i = 0; i < dp[maxi]; i++) {
        if (arr[i] < arr[maxi])
            newarr[num++] = arr[i];
    }
    newarr[num] = arr[maxi];
    return newarr;
}

int main(void)
{
    int arr[] = {2,1,5,3,6,4,8,9,7};
    int size;
    int *newarr = LIS(arr, sizeof(arr)/sizeof(arr[0]), &size);

    for (int i = 0; i < size; i++)
        printf("%d ", newarr[i]);

    return 0;
}