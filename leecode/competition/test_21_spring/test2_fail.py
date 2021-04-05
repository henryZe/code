from typing import List

class Solution:
    # O(n^2)
    def orchestraLayout(self, num: int, xPos: int, yPos: int) -> int:
        directions = ((0, 1), (1, 0), (0, -1), (-1, 0))
        dir_index = 0
        ans = 1
        row, col = 0, 0
        visited = []
        for _ in range(num):
            visited.append([False] * num)

        while row != xPos or col != yPos:
            visited[row][col] = True
            nextRow, nextCol = row + directions[dir_index][0], col + directions[dir_index][1]
            if not (0 <= nextRow < num) or not (0 <= nextCol < num) or visited[nextRow][nextCol]:
                dir_index = (dir_index + 1) % 4
            row += directions[dir_index][0]
            col += directions[dir_index][1]
            ans += 1

        ans %= 9
        if not ans:
            ans = 9
        return ans

# num = 3
# Xpos = 0
# Ypos = 2
num = 4
Xpos = 1
Ypos = 2
print(Solution().orchestraLayout(num, Xpos, Ypos))
