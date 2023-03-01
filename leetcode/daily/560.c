// O(N^2)
int subarraySum(int* nums, int numsSize, int k)
{
    int i, j;
    int res = 0;
    int *sum = malloc((numsSize + 1) * sizeof(int));

    sum[0] = 0;
    for (i = 1; i <= numsSize; i++) {
        sum[i] = sum[i - 1] + nums[i - 1];
    }

    for (i = 0; i <= numsSize; i++) {
        for (j = i + 1; j <= numsSize; j++) {
            int diff = sum[j] - sum[i];
            if (diff == k) {
                // printf("i = %d j = %d\n", i, j);
                res++;
            }
        }
    }

    return res;
}
