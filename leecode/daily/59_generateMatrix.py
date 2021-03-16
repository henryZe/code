from typing import List

class Solution:
    def generateMatrix(self, n: int) -> List[List[int]]:
        if n <= 0:
            return []

        # right, down, left, up
        directions = ((0, 1), (1, 0), (0, -1), (-1, 0))
        dir_index = 0
        row, col = 0, 0
        matrix = [[0] * n for _ in range(n)]
        total = n * n

        for i in range(1, total + 1):
            matrix[row][col] = i
            nextRow, nextCol = row + directions[dir_index][0], col + directions[dir_index][1]
            if not (0 <= nextRow < n) or not (0 <= nextCol < n) or matrix[nextRow][nextCol]:
                dir_index = (dir_index + 1) % 4
            row += directions[dir_index][0]
            col += directions[dir_index][1]

        return matrix


n = 5
matrix = Solution().generateMatrix(n)
for l in matrix:
    print(l)