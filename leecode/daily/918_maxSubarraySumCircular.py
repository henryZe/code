from typing import List

class Solution:
    def maxSubarraySumCircular(self, nums: List[int]) -> int:
        # dp
        n = len(nums)
        cur_sum = [0] * n
        cur_sum[0] = nums[0]

        # case mid: max subarray
        for i in range(1, n):
            cur_sum[i] = nums[i]
            if cur_sum[i - 1] > 0:
                cur_sum[i] += cur_sum[i - 1]

        cur_min = [0] * n
        cur_min[0] = nums[0]

        for i in range(1, n):
            cur_min[i] = nums[i]
            if cur_min[i - 1] < 0:
                cur_min[i] += cur_min[i - 1]

        # case tail -> head: max subarray
        if sum(nums) == min(cur_min):
            # all nums is negative
            return max(cur_sum)

        return max(max(cur_sum), sum(nums) - min(cur_min))

nums = [
    [1,-2,3,-2],
    [5,-3,5],
    [3,-1,2,-1],
    [3,-2,2,-3],
    [-2,-3,-1],
]
for i in nums:
    print(Solution().maxSubarraySumCircular(i))
