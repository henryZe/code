from typing import List

class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        # greedy
        pre_sum = 0
        cur_sum = nums[0]
        max_sum = nums[0]

        for i in nums:
            cur_sum = pre_sum + i

            if cur_sum < 0:
                pre_sum = 0
            else:
                pre_sum = cur_sum
    
            if cur_sum > max_sum:
                max_sum = cur_sum

        return max_sum

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
