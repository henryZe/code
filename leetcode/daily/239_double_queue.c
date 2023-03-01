// O(N)
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize)
{
    int *dequeue = malloc(sizeof(int) * numsSize);
    int left = 0, right = 0;

    int *ans = malloc(sizeof(int) * numsSize);
    int len = 0;

    for (int i = 0; i < numsSize; i++) {
        // if dequeue not empty, keep the queue decrease
        while (left < right && nums[dequeue[right - 1]] < nums[i]) {
            right--;
        }
        dequeue[right++] = i;

        while (dequeue[left] < (i - k + 1)) {
            left++;
        }

        if (i >= (k - 1)) {
            ans[len++] = nums[dequeue[left]];
        }
    }

    *returnSize = len;
    return ans;
}
