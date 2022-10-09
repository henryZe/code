from typing import List

class Solution:
    def numberOfPaths(self, grid: List[List[int]], k: int) -> int:
        n = len(grid)
        m = len(grid[0])
        MOD = 10**9 + 7

        f = [[[0] * k for j in range(m + 1)] for i in range(n + 1)]
        # start point (make f[0 + 1][0 + 1][grid[0][0] % k] = 1)
        f[0][1][0] = 1

        # O(n * m * k)
        for i, row in enumerate(grid):
            for j, val in enumerate(row):
                for v in range(k):
                    f[i + 1][j + 1][(v + val) % k] = (f[i][j + 1][v] + f[i + 1][j][v]) % MOD
        return f[n][m][0]


# grid = [[5,2,4],[3,0,5],[0,7,2]]
# k = 3
# grid = [[0,0]]
# k = 5
grid = [[7,3,4,9],[2,3,6,2],[2,3,7,0]]
k = 1
print(Solution().numberOfPaths(grid, k))
