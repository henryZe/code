from typing import List

class Solution:
    def largestLocal(self, grid: List[List[int]]) -> List[List[int]]:
        n = len(grid)
        local = []
        for i in range(n - 2):
                local.append([1] * (n - 2))

        for i in range(n - 2):
                for j in range(n - 2):
                        local_max = 1
                        for row in range(3):
                                local_max = max(max(grid[i + row][j:j+3]), local_max)
                        local[i][j] = local_max

        return local

# grid = [[9,9,8,1],[5,6,2,6],[8,2,6,4],[6,2,2,2]]
grid = [[1,1,1,1,1],[1,1,1,1,1],[1,1,2,1,1],[1,1,1,1,1],[1,1,1,1,1]]
print(Solution().largestLocal(grid))
