from typing import List

class Solution:
    def leastBricks(self, wall: List[List[int]]) -> int:
        d = {}
        n = len(wall)

        for i in range(n):
            j = len(wall[i])
            sumv = 0
            for brick in range(j - 1):
                sumv += wall[i][brick]
                if sumv in d:
                    d[sumv] += 1
                else:
                    d[sumv] = 1

        if not d.values():
            return len(wall)

        return len(wall) - max(d.values())

# w = [[1,2,2,1],[3,1,2],[1,3,2],[2,4],[3,1,2],[1,3,1,1]]
w = [[1],[1],[1]]
print(Solution().leastBricks(w))
