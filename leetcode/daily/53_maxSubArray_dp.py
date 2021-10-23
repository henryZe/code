from typing import List

class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        # dp
        n = len(nums)
        cur_sum = [0] * n
        cur_sum[0] = nums[0]

        for i in range(1, n):
            cur_sum[i] = nums[i]
            if cur_sum[i - 1] > 0:
                cur_sum[i] += cur_sum[i - 1]

        return max(cur_sum)

nums = [
    [-2,1,-3,4,-1,2,1,-5,4],
    [1],
    [0],
    [-1],
    [-100000],
    [-2,-1],
]
for i in nums:
    print(Solution().maxSubArray(i))
