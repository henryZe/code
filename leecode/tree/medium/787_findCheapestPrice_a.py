from typing import List

class Solution:
    # dynamic programming
    def findCheapestPrice(self, n: int, flights: List[List[int]], src: int, dst: int, K: int) -> int:
        prices = []
        for _ in range(2):
            prices.append([float('inf')] * n)
        prices[0][src] = prices[1][src] = 0

        for i in range(K + 1):
            for s, d, w in flights:
                prices[i & 1][d] = min(prices[i & 1][d], prices[~i & 1][s] + w)

        return prices[K & 1][dst] if prices[K & 1][dst] < float('inf') else -1


n = 3
edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0
dst = 2
k = 1
print(Solution().findCheapestPrice(n, edges, src, dst, k))
