from typing import List

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)
        p = [[-prices[0], 0, 0]]
        for i in range(n - 1):
            p.append([0, 0, 0])

        for i in range(1, n):
            p[i][0] = max(p[i-1][0], p[i-1][2] - prices[i])
            p[i][1] = max(p[i-1][1], p[i-1][0] + prices[i])
            p[i][2] = max(p[i-1][1], p[i-1][2])

        return max(p[n-1][1], p[n-1][2])

price = [1,2,3,0,2]
print(Solution().maxProfit(price))