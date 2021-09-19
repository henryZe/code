from typing import List

class Solution:
    def maxProfit(self, prices: List[int], fee: int) -> int:
        n = len(prices)
        p = [[-prices[0], 0]]
        for i in range(1, n):
            p.append([0, 0])

        for i in range(1, n):
            p[i][0] = max(p[i-1][0], p[i-1][1] - prices[i])
            p[i][1] = max(p[i-1][0] + prices[i] - fee, p[i-1][1])

        return p[n-1][1]

# prices = [1, 3, 2, 8, 4, 9]
# fee = 2
prices = [1,3,7,5,10,3]
fee = 3
print(Solution().maxProfit(prices, fee))
