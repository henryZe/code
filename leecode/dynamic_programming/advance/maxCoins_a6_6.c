#include "math.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"

int rec[502][502];
int val[502];

int solve(int left, int right)
{
    if (left >= right - 1)
        return 0;

    if (rec[left][right] != -1)
        return rec[left][right];

    for (int i = left + 1; i < right; i++) {
        int sum = val[left] * val[i] * val[right];
        sum += solve(left, i) + solve(i, right);
        rec[left][right] = fmax(rec[left][right], sum);
    }

    return rec[left][right];
}

int maxCoins(int* nums, int numsSize)
{
    int i;

    memset(rec, -1, sizeof(rec));
    val[0] = val[numsSize + 1] = 1;

    for (i = 1; i < numsSize + 1; i++) {
        val[i] = nums[i - 1];
    }

    return solve(0, numsSize + 1);
}

int main(void)
{
    int nums[] = {3,1,5,8};
    printf("%d\n", maxCoins(nums, 4));
    return 0;
}
