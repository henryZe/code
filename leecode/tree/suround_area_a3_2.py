from typing import List

grid = [
    ["X","O","X","O","X","O"],
    ["O","X","O","X","O","X"],
    ["X","O","X","O","X","O"],
    ["O","X","O","X","O","X"]
]

class Solution:
    def solve(self, board: List[List[str]]) -> None:
        def dfs(x: int, y: int):
            if not 0 <= x < r or not 0 <= y < c or board[x][y] != 'O':
                return

            board[x][y] = 'a'
            dfs(x - 1, y)
            dfs(x + 1, y)
            dfs(x, y - 1)
            dfs(x, y + 1)
            return

        if not board:
            return

        r = len(board)
        c = len(board[0])

        for x in range(r):
            dfs(x, 0)
            dfs(x, c - 1)

        for y in range(c):
            dfs(0, y)
            dfs(r - 1, y)

        for x in range(r):
            for y in range(c):
                if board[x][y] == "a":
                    board[x][y] = 'O'
                else:
                    board[x][y] = 'X'

        return

Solution().solve(grid)
print(grid)
