from typing import List

class Solution:
    def rob(self, nums: List[int]) -> int:
        def robRange(start: int, end: int) -> int:
            for i in range(start, end):
                if i == start:
                    dp[i] = nums[start]
                elif i == start + 1:
                    dp[i] = max(nums[start], nums[start + 1])
                else:
                    dp[i] = max(dp[i - 1], dp[i - 2] + nums[i])
            return dp[end - 1]

        if not nums:
            return 0

        n = len(nums)
        if n == 1:
            return nums[0]

        dp = [0] * n
        return max(robRange(0, n - 1), robRange(1, n))

# nums = [2,3,2]
# nums = [1,2,3,1]
# nums = [1]
nums = [2,1,1,2]
print(Solution().rob(nums))
