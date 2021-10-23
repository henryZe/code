from typing import List

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)
        left = prices[0]
        max_profix = 0

        for i in prices:
            if i < left:
                left = i
            else:
                cur_profix = i - left
                max_profix = max(max_profix, cur_profix)

        return max_profix

nums = [
    [7,1,5,3,6,4],
    [7,6,4,3,1],
]
for i in nums:
    print(Solution().maxProfit(i))
