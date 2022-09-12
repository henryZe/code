import imp
from typing import List

class Solution:
    def sellingWood(self, m: int, n: int, prices: List[List[int]]) -> int:
        price_h = {}
        for h, w, p in prices:
            price_h[(h, w)] = p

        dp = []
        for _ in range(m + 1):
            dp.append([0] * (n + 1))

        for i in range(1 + m):
            for j in range(1 + n):
                dp[i][j] = max(price_h.get((i, j), 0),
                                max((dp[i][k] + dp[i][j - k] for k in range(1, j)), default = 0),
                                max((dp[k][j] + dp[i - k][j] for k in range(1, i)), default = 0))
        return dp[m][n]

# m = 3
# n = 5
# prices = [[1,4,2],[2,2,7],[2,1,3]]
m = 4
n = 6
prices = [[3,2,10],[1,4,2],[4,1,3]]
print(Solution().sellingWood(m, n, prices))
