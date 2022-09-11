from typing import List

class Solution:
    def maximumImportance(self, n: int, roads: List[List[int]]) -> int:
        degree = [0] * n
        for w, v in roads:
            degree[w] += 1
            degree[v] += 1
        degree.sort()

        res = 0
        for d, i in enumerate(degree, 1):
            res += d * i

        return res

# n = 5
# roads = [[0,1],[1,2],[2,3],[0,2],[1,3],[2,4]]
n = 5
roads = [[0,3],[2,4],[1,3]]
print(Solution().maximumImportance(n, roads))
