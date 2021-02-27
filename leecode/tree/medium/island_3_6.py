from typing import List

grid = [
    ["1","1","0","0","0"],
    ["1","1","0","0","0"],
    ["0","0","1","0","0"],
    ["0","0","0","1","1"]
]

class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        def dfs(grid: List[List[str]], r_max: int, c_max: int, r: int, c: int):
            grid[r][c] = '0'

            if (r - 1 >= 0 and grid[r - 1][c] == '1'):
                dfs(grid, r_max, c_max, r - 1, c)
            if (r + 1 < r_max and grid[r + 1][c] == '1'):
                dfs(grid, r_max, c_max, r + 1, c)

            if (c - 1 >= 0 and grid[r][c - 1] == '1'):
                dfs(grid, r_max, c_max, r, c - 1)
            if (c + 1 < c_max and grid[r][c + 1] == '1'):
                dfs(grid, r_max, c_max, r, c + 1)

            return

        r = len(grid)
        c = len(grid[0])
        isalandnum = 0

        for i in range(r):
            for j in range(c):
                if grid[i][j] == '1':
                    isalandnum += 1
                    dfs(grid, r, c, i, j)

        return isalandnum

obj = Solution()
print(obj.numIslands(grid))
