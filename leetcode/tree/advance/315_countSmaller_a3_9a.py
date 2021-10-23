from typing import List
import bisect

# O(n^2)
# 暴力算法
# class Solution:
#     def countSmaller(self, nums: List[int]) -> List[int]:
#         if not nums:
#             return []
# 
#         size = len(nums)
#         counts = [0] * size
# 
#         for i in range(size):
#             for j in range(i + 1, size):
#                 if nums[i] > nums[j]:
#                     counts[i] += 1
# 
#         return counts

# O(n^2)
# 插入排序
class Solution:
    def countSmaller(self, nums: List[int]) -> List[int]:
        if not nums:
            return []

        size = len(nums)
        counts = [0] * size
        ordered = []

        for i in range(size - 1, -1, -1):
            counts[i] = bisect.bisect_left(ordered, nums[i])
            ordered.insert(counts[i], nums[i])

        return counts


nums = [5,2,6,1]
# nums = [-1,-1]
print(Solution().countSmaller(nums))
