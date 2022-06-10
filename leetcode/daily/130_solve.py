import collections
from typing import List
import collections

class Solution:
    def solve(self, board: List[List[str]]) -> None:
        m = len(board)
        n = len(board[0])

        # bfs
        q = collections.deque()
        for i in range(n):
            if board[0][i] == 'O':
                q.append((0, i))
                board[0][i] = 'A'
            if board[m - 1][i] == 'O':
                q.append((m - 1, i))
                board[m - 1][i] = 'A'

        for j in range(m):
            if board[j][0] == 'O':
                q.append((j, 0))
                board[j][0] = 'A'
            if board[j][n - 1] == 'O':
                q.append((j, n - 1))
                board[j][n - 1] = 'A'

        while q:
            x, y = q.popleft()
            for mx, my in [(x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)]:
                if 0 <= mx < m and 0 <= my < n:
                    if board[mx][my] == 'O':
                        board[mx][my] = 'A'
                        q.append((mx, my))

        for i in range(m):
            for j in range(n):
                if board[i][j] == 'A':
                    board[i][j] = 'O'
                elif board[i][j] == 'O':
                    board[i][j] = 'X'

        return

b = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
Solution().solve(b)
print(b)
