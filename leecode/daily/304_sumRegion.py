from typing import List

# class NumMatrix:
#     def __init__(self, matrix: List[List[int]]):
#         self.matrix = None
#         if not matrix:
#             return
#         if not matrix[0]:
#             return

#         self.matrix = []
#         row = len(matrix)
#         col = len(matrix[0])
#         for i in range(row):
#             self.matrix.append([])
#             for j in range(col):
#                 self.matrix[i].append(matrix[i][j])
#         return

#     def sumRegion(self, row1: int, col1: int, row2: int, col2: int) -> int:
#         if not self.matrix:
#             return -1

#         res = 0
#         for x in range(row1, row2 + 1):
#             res += sum(self.matrix[x][col1:col2 + 1])
#         return res

# 计算复杂度：O(n * m)
# 空间复杂度：O(n * m)

# class NumMatrix:
#     def __init__(self, matrix: List[List[int]]):
#         row = len(matrix)
#         col = len(matrix[0]) if matrix else 0

#         self.sums = []
#         for i in range(row):
#             self.sums.append([0] * (col + 1))

#         for i in range(row):
#             for j in range(col):
#                 self.sums[i][j+1] = self.sums[i][j] + matrix[i][j]
#         return

#     def sumRegion(self, row1: int, col1: int, row2: int, col2: int) -> int:
#         res = 0
#         for x in range(row1, row2 + 1):
#             res += self.sums[x][col2 + 1] - self.sums[x][col1]
#         return res

# 计算复杂度：O(n)
# 空间复杂度：O(n * m)

class NumMatrix:
    def __init__(self, matrix: List[List[int]]):
        row = len(matrix)
        col = len(matrix[0]) if matrix else 0

        self.sums = []
        for i in range(row + 1):
            self.sums.append([0] * (col + 1))

        for i in range(row):
            for j in range(col):
                self.sums[i+1][j+1] = self.sums[i][j+1] + self.sums[i+1][j] - self.sums[i][j] + matrix[i][j]
        return

    def sumRegion(self, row1: int, col1: int, row2: int, col2: int) -> int:
        return self.sums[row2 + 1][col2 + 1] - self.sums[row2 + 1][col1] - self.sums[row1][col2 + 1] + self.sums[row1][col1]

# 计算复杂度：O(1)
# 空间复杂度：O(n * m)

matrix = [
    [3, 0, 1, 4, 2],
    [5, 6, 3, 2, 1],
    [1, 2, 0, 1, 5],
    [4, 1, 0, 1, 7],
    [1, 0, 3, 0, 5]
]
obj = NumMatrix(matrix)
print(obj.sumRegion(2, 1, 4, 3))
