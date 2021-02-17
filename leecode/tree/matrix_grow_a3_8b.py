from typing import List
import collections

class Solution:
    # BFS
    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        if not matrix:
            return 0

        dirs = [[-1, 0], [1, 0], [0, -1], [0, 1]]

        r_len = len(matrix)
        c_len = len(matrix[0])
        outdegree = [[0] * c_len for _ in range(r_len)]
        q = collections.deque()
        for r in range(r_len):
            for c in range(c_len):
                for d in dirs:
                    r_new, c_new = r + d[0], c + d[1]
                    if 0 <= r_new < r_len and 0 <= c_new < c_len and matrix[r][c] < matrix[r_new][c_new]:
                        outdegree[r][c] += 1
                if outdegree[r][c] == 0:
                    q.append((r, c))

        ans = 0
        while q:
            ans += 1
            q_len = len(q)

            for _ in range(q_len):
                r, c = q.popleft()
                for d in dirs:
                    r_new, c_new = r + d[0], c + d[1]
                    if 0 <= r_new < r_len and 0 <= c_new < c_len and matrix[r][c] > matrix[r_new][c_new]:
                        outdegree[r_new][c_new] -= 1
                        if outdegree[r_new][c_new] == 0:
                            q.append((r_new, c_new))

        return ans


matrix = [
    [3,4,5],
    [3,2,6],
    [2,2,1]
]
print(Solution().longestIncreasingPath(matrix))

