from typing import List

class Solution:
    def maxScoreSightseeingPair(self, values: List[int]) -> int:
        n = len(values)
        max_sol = 0

        # O(n^2)
        # for i in range(0, n):
        #     for j in range(i + 1, n):
        #         cur = values[i] + values[j] + i - j
        #         max_sol = max(max_sol, cur)

        # O(n)
        cur_pair = values[0]
        for i in range(1, n):
            cur_sol = cur_pair + values[i] - i
            max_sol = max(max_sol, cur_sol)
            cur_pair = max(cur_pair, values[i] + i)

        return max_sol

nums = [
    [8,1,5,2,6],
    [1,2],
]
for i in nums:
    print(Solution().maxScoreSightseeingPair(i))
