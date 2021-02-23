from typing import List
import functools

class Solution:
    dirs = [[-1, 0], [1, 0], [0, -1], [0, 1]]

    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        if not matrix:
            return 0

        # DFS
        @functools.lru_cache(None)
        def dfs(r: int, c: int) -> int:
            best = 1
            for d in self.dirs:
                r_new = r + d[0]
                c_new = c + d[1]
                if 0 <= r_new < r_len and 0 <= c_new < c_len and matrix[r][c] < matrix[r_new][c_new]:
                    best = max(best, dfs(r_new, c_new) + 1)
            return best

        r_len = len(matrix)
        c_len = len(matrix[0])
        ans = 0

        for r in range(r_len):
            for c in range(c_len):
                ans = max(ans, dfs(r, c))

        return ans


matrix = [
    [3,4,5],
    [3,2,6],
    [2,2,1]
]
print(Solution().longestIncreasingPath(matrix))

