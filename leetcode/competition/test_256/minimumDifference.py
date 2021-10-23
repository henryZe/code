from typing import List
from sortedcontainers import SortedList

class Solution:
    def minimumDifference(self, nums: List[int], k: int) -> int:
        slist = SortedList(nums)
        size = len(slist)
        diff = float("inf")

        for i in range(size - k + 1):
            diff = min(max(slist[i:i+k]) - min(slist[i:i+k]), diff)

        return diff

print(Solution().minimumDifference([9,4,1,7], 2))