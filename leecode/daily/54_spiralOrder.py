from typing import List

class Solution:
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        ret = []

        if not matrix or not matrix[0]:
            return ret

        # right, down, left, up
        directions = ((0, 1), (1, 0), (0, -1), (-1, 0))
        dir_index = 0
        row, col = 0, 0

        n = len(matrix)
        m = len(matrix[0])
        visited = [[False] * m for _ in range(n)]
        total = n * m
        order = [0] * total

        for i in range(total):
            order[i] = matrix[row][col]
            visited[row][col] = True
            nextRow, nextCol = row + directions[dir_index][0], col + directions[dir_index][1]
            if not (0 <= nextRow < n) or not (0 <= nextCol < m) or visited[nextRow][nextCol]:
                dir_index = (dir_index + 1) % 4
            row += directions[dir_index][0]
            col += directions[dir_index][1]

        return order

matrix = [[1,2,3],[4,5,6],[7,8,9]]
print(Solution().spiralOrder(matrix))
