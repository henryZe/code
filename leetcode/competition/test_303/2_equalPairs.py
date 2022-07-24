from typing import List

class Solution:
    def equalPairs(self, grid: List[List[int]]) -> int:
        l = len(grid)
        cols = [[0] * l for _ in range(l)]

        for i in range(l):
            for j in range(l):
                cols[j][i] = grid[i][j]

        count = 0
        for i in range(l):
            for j in range(l):
                if grid[i] == cols[j]:
                        count += 1

        return count


grid = [[3,2,1],[1,7,6],[2,7,7]]
# grid = [[3,1,2,2],[1,4,4,5],[2,4,2,2],[2,4,2,2]]
print(Solution().equalPairs(grid))
