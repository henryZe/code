from turtle import right
from typing import List
import heapq

class Solution:
    def minGroups(self, intervals: List[List[int]]) -> int:
        intervals.sort()
        h = []
        for left, right in intervals:
            if h and h[0] < left:
                heapq.heappop(h)
            heapq.heappush(h, right)

        return len(h)


# intervals = [[5,10],[6,8],[1,5],[2,3],[1,10]]
intervals = [[1,3],[5,6],[8,10],[11,13]]
print(Solution().minGroups(intervals))
