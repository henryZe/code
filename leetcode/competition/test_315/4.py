from typing import List

class Solution:
    def countSubarrays(self, nums: List[int], minK: int, maxK: int) -> int:
        pmin = -1
        pmax = -1
        res = 0
        l = 0

        for r, x in enumerate(nums):
            if x == minK:
                pmin = r
            if x == maxK:
                pmax = r

            if minK <= x <= maxK:
                if l <= min(pmax, pmin):
                    res += min(pmax, pmin) - l + 1
            else:
                l = r + 1

        return res

# nums = [1,3,5,2,7,5]
# minK = 1
# maxK = 5
nums = [1,1,1,1]
minK = 1
maxK = 1
print(Solution().countSubarrays(nums, minK, maxK))
