from typing import List

class Solution:
    def validPartition(self, nums: List[int]) -> bool:
        n = len(nums)
        dp = [True] + [False] * n

        for i in range(n):
            if i > 0 and dp[i - 1] and nums[i] == nums[i - 1] or \
                i > 1 and dp[i - 2] and (nums[i] == nums[i - 1] == nums[i - 2] or \
                                        nums[i] == nums[i - 1] + 1 == nums[i - 2] + 2):
                dp[i + 1] = True

        return dp[n]

nums = [4,4,4,5,6]
# nums = [1,1,1,2]
print(Solution().validPartition(nums))
