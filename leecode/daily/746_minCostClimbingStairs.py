from typing import List

class Solution:
    def minCostClimbingStairs(self, cost: List[int]) -> int:
        size = len(cost)
        f = [float("inf")] * (size + 1)
        f[0] = 0
        f[1] = 0

        for i in range(2, size + 1):
            f[i] = min(f[i - 1] + cost[i - 1], f[i - 2] + cost[i - 2])

        return f[-1]

print(Solution().minCostClimbingStairs([10, 15, 20]))
print(Solution().minCostClimbingStairs([1, 100, 1, 1, 1, 100, 1, 1, 100, 1]))
