from typing import List

class Solution:
    # time O(log(m * n))
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        m = len(matrix)
        n = len(matrix[0])

        left = 0
        right = m * n - 1
        while left <= right:
            mid = (left + right) // 2
            if matrix[mid // n][mid % n] < target:
                left = mid + 1
            elif matrix[mid // n][mid % n] > target:
                right = mid - 1
            else:
                return True

        return False

# matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]]
# target = 3
matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]]
target = 13
print(Solution().searchMatrix(matrix, target))
