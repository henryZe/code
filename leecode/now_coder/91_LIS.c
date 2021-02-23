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

    int max_len = 0;
    for (int i = 0; i < arrLen; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j]) {
                dp[i] = fmax(dp[i], dp[j] + 1);
                if (dp[i] > max_len) {
                    max_len = dp[i];
                }
            }
        }
    }

    int *newarr = (int *)malloc(sizeof(int) * max_len);
    int cur = max_len;
    for (int i = arrLen - 1; i >= 0; i--) {
        if (dp[i] == cur)
            newarr[--cur] = arr[i];
    }

    *returnSize = max_len;
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