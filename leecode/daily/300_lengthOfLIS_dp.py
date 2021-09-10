from typing import List

class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        n = len(nums)
        dp = [1] * n

        for i in range(n):
            for j in range(i):
                if nums[j] < nums[i]:
                    dp[i] = max(dp[j] + 1, dp[i])

        return max(dp)

nums = [10,9,2,5,3,7,101,18]
# nums = [0,1,0,3,2,3]
# nums = [7,7,7,7,7,7,7]
print(Solution().lengthOfLIS(nums))
