from typing import List
import bisect

class Solution:
    # 计算复杂度：O(n^2)
    # def maxEnvelopes(self, envelopes: List[List[int]]) -> int:
    #     if not envelopes:
    #         return 0
    # 
    #     # sort increase by x[0], and decrease by x[1]
    #     envelopes.sort(key = lambda x:(x[0], -x[1]))
    #     size = len(envelopes)
    # 
    #     dp = [1] * size
    #     for i in range(size):
    #         for j in range(i):
    #             if envelopes[i][1] > envelopes[j][1]:
    #                 dp[i] = max(dp[i], dp[j] + 1)
    # 
    #     return max(dp)

    # 计算复杂度：O(n * log(n))
    def maxEnvelopes(self, envelopes: List[List[int]]) -> int:
        if not envelopes:
            return 0
    
        # sort increase by x[0], and decrease by x[1]
        envelopes.sort(key = lambda x:(x[0], -x[1]))
        size = len(envelopes)

        increase = [envelopes[0][1]]
        for i in range(size):
            num = envelopes[i][1]
            if num > increase[-1]:
                increase.append(num)
            else:
                index = bisect.bisect_left(increase, num)
                increase[index] = num

        return len(increase)


envelopes = [[5,4],[6,4],[6,7],[2,3]]
print(Solution().maxEnvelopes(envelopes))
