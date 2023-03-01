int longestOnes(int* nums, int numsSize, int k)
{
    int cur_res = 0, res = 0;
    int start = 0, end = 0;
    int cur_k = 0;

    while (end < numsSize) {
        cur_k += (nums[end] == 0) ? 1 : 0;

        while (cur_k > k) {
            cur_k -= (nums[start] == 0) ? 1 : 0;
            start++;
        }

        end++;
        cur_res = end - start;
        res = (cur_res > res) ? cur_res : res;
    }

    return res;
}
