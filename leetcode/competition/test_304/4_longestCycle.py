from typing import List

class Solution:
    def __init__(self) -> None:
        self.clock = 0
        self.h = {}

    def draw(self, node, edge):
        startTime = self.clock

        while node not in self.h:
            self.h[node] = self.clock
            self.clock += 1

            node = edge[node]
            if node == -1:
                return -1

        if self.h[node] < startTime:
            return -1

        return self.clock - self.h[node]

    def longestCycle(self, edges: List[int]) -> int:
        res = -1
        for i in range(len(edges)):
            cur = self.draw(i, edges)
            if cur > res:
                res = cur
        return res

edges = [3,3,4,2,3]
# edges = [2,-1,3,1]
# edges = [-1,4,-1,2,0,4]
print(Solution().longestCycle(edges))
