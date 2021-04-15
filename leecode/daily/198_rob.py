from typing import List

class Solution:
    def rob(self, nums: List[int]) -> int:
        if not nums:
            return 0
        
        n = len(nums)
        dp = [0] * n
        for i in range(n):
            if i == 0:
                dp[i] = nums[0]
            elif i == 1:
                dp[i] = max(nums[0], nums[1])
            else:
                dp[i] = max(dp[i - 1], dp[i - 2] + nums[i])

        return dp[n - 1]

nums = [2,3,2]
print(Solution().rob(nums))
