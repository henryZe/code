#include <stdio.h>
#include <stdlib.h>

void print_arr(int *p, int size)
{
    for (int i = 0; i < size; i++) {
        printf("%d ", p[i]);
    }
}

int* LIS(int* arr, int arrLen, int* returnSize )
{
    if (!arrLen || arrLen < 1) {
        *returnSize = 0;
        return 0;
    }

    int dp[arrLen];
    int len_arr[arrLen];
    int len = 1;
    dp[0] = arr[0];
    len_arr[0] = 1;

    for (int i = 1; i < arrLen; i++) {
        if (arr[i] > dp[len - 1]) {
            len++;
            dp[len - 1] = arr[i];
            len_arr[i] = len;
            
        } else {
            int l = 0, r = len - 1;
            int pos = r;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (dp[mid] < arr[i]) {
                    l = mid + 1;
                } else {
                    pos = mid;
                    r = mid - 1;
                }
            }
            dp[pos] = arr[i];
            len_arr[i] = pos + 1;
        }
    }

    // printf("dp:\n");
    // print_arr(dp, len);
    // printf("\n");

    // printf("len_arr:\n");
    // print_arr(len_arr, arrLen);
    // printf("\n");

    *returnSize = len;
    int *ret = (int *)malloc(len * sizeof(int));

    for (int i = arrLen - 1; i >= 0; i--) {
        if (len_arr[i] == len) {
            ret[len - 1] = arr[i];
            len--;
        }
    }

    return ret;
}

int main(void)
{
    // int arr[] = {2,1,5,3,6,4,8,9,7,2,3,4,5};
    int arr[] = {2,1,5,3,6,4,8,9,7};
    int size;
    int *newarr = LIS(arr, sizeof(arr)/sizeof(arr[0]), &size);

    for (int i = 0; i < size; i++) {
        printf("%d ", newarr[i]);
    }
    printf("\n");
    return 0;
}
