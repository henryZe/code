from typing import List

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        # n = len(prices)
        # left = prices[0]
        # left_valid = False
        # right = 0
        # cur_max = 0

        # for i in prices[1:]:
        #     if left_valid == False:
        #         if left >= i:
        #             left = i
        #         else:
        #             left_valid = True
        #             right = i

        #     else:
        #         if right <= i:
        #             right = i
        #         else:
        #             cur_max += right - left
        #             left_valid = False
        #             left = i

        # if left_valid == True:
        #     cur_max += right - left

        # return cur_max

        # greedy
        last = prices[0]
        profit = 0
        for i in prices[1:]:
            profit += max(0, i - last)
            last = i
        return profit

nums = [
    [7,1,5,3,6,4],
    [1,2,3,4,5],
    [7,6,4,3,1],
]
for i in nums:
    print(Solution().maxProfit(i))