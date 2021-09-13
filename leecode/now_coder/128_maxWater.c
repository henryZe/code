#include <stdio.h>
#include <stdlib.h>

long long cal_water(int* arr, int arrLen, int eq)
{
    long long ret = 0;
    int l = 0, r = 0;

    while (r < arrLen) {
        for (r = l + 1; r < arrLen; r++) {
            if (arr[l] < arr[r])
                break;

            if (eq && arr[l] == arr[r])
                break;
        }

        if (r < arrLen) {
            for (int i = l + 1; i < r; i++) {
                ret += arr[l] - arr[i];
            }
            l = r;
        }
    }

    return ret;
}

long long maxWater(int* arr, int arrLen )
{
    int *rev_arr = (int *)malloc(arrLen * sizeof(int));
    for (int i = 0; i < arrLen; i++) {
        rev_arr[i] = arr[arrLen - 1 - i];
    }

    return cal_water(arr, arrLen, 1) + cal_water(rev_arr, arrLen, 0);
}

int main(void)
{
    int arr[] = {3,1,2,5,2,4};
    int ret = maxWater(arr, sizeof(arr) / sizeof(arr[0]));
    printf("%d\n", ret);
    return 0;
}