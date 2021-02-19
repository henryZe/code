import math

class Solution:
    def numSquares(self, n: int) -> int:
        square_nums = [i**2 for i in range(1, int(math.sqrt(n)) + 1)]
        dp = [float('inf')] * (n + 1)
        dp[0] = 0

        for i in range(1, n + 1):
            for square in square_nums:
                if square > i:
                    break
                dp[i] = min(dp[i], dp[i - square] + 1)

        return dp[n]


print(Solution().numSquares(13))
