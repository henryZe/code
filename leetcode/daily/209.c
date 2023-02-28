int minSubArrayLen(int target, int* nums, int numsSize)
{
    int start = 0, end = 0;
    int sum = 0;
    int res = numsSize + 1;

    while (end < numsSize) {
        sum += nums[end];
        // printf("end %d\n", end);

        while (sum >= target) {
            int cur = end - start + 1;
            res = cur < res ? cur : res;
            // printf("res %d\n", res);

            sum -= nums[start];
            start++;
        }

        end++;
    }

    if (res == numsSize + 1)
        // no case meets condition
        return 0;

    return res;
}
