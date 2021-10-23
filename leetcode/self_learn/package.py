from typing import List

# 递归
# class Solution:
#     def packageValue(self, capacity: int, value: List[int], weight: List[int]) -> int:
#         def calcValue(index: int, c: int) -> int:
#             if index >= len(value):
#                 return 0
#
#             if weight[index] > c:
#                 result = calcValue(index + 1, c)
#             else:
#                 v1 = calcValue(index + 1, c - weight[index]) + value[index]
#                 v2 = calcValue(index + 1, c)
#                 result = max(v1, v2)
#
#             return result
#
#         return calcValue(0, capacity)

# dynamic programming
class Solution:
    def packageValue(self, capacity: int, value: List[int], weight: List[int]) -> int:
        size = len(value)
        res = []
        for _ in range(size):
            res.append([0] * (capacity + 1))

        def calcValue(index: int, c: int) -> int:
            if index >= len(value):
                return 0

            if res[index][c]:
                return res[index][c]

            if weight[index] > c:
                res[index][c] = calcValue(index + 1, c)
            else:
                v1 = calcValue(index + 1, c - weight[index]) + value[index]
                v2 = calcValue(index + 1, c)
                res[index][c] = max(v1, v2)

            return res[index][c]

        return calcValue(0, capacity)

vs = [2,4,3,7]
ws = [2,3,5,5]
print(Solution().packageValue(10, vs, ws))
