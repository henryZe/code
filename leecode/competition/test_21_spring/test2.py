from typing import List

class Solution:
    # O(1)
    def orchestraLayout(self, num: int, xPos: int, yPos: int) -> int:
        # 位于第几圈
        T = min(num - xPos - 1, num - yPos - 1, xPos, yPos)
        # 等差数列 -0, -2, -4, -6 ... -2T, 之和 = -(0 + 2T) / 2 = -T
        # 故每层边长：n - T
        # 个数: 4 * (n - T) * T, 4 * 边长 * 层数 
        v = 4 * T * (num - T) % 9

        start, end = T, num - T - 1
        if xPos == start:
            return (v + yPos - start) % 9 + 1
        elif yPos == end:
            return (v + (end - start) + xPos - start) % 9 + 1
        elif xPos == end:
            return (v + 2 * (end - start) + end - yPos) % 9 + 1
        elif yPos == start:
            return (v + 3 * (end - start) + end - xPos) % 9 + 1

        return 0

# num = 3
# Xpos = 0
# Ypos = 2
num = 5
Xpos = 3
Ypos = 2
print(Solution().orchestraLayout(num, Xpos, Ypos))
