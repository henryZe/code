from typing import List

# O(n^2)
# class Solution:
#     def nextGreaterElements(self, nums: List[int]) -> List[int]:
#         size = len(nums)
#         nums.extend(nums)
#         res = [-1] * size
#         for i in range(size):
#             for j in range(i + 1, i + size):
#                 if nums[j] > nums[i]:
#                     res[i] = nums[j]
#                     break
#         return res

# O(n)
# 单调栈
class Solution:
    def nextGreaterElements(self, nums: List[int]) -> List[int]:
        size = len(nums)
        res = [-1] * size
        stk = []
        for i in range(size * 2 - 1):
            while stk and nums[stk[-1]] < nums[i % size]:
                res[stk.pop()] = nums[i % size]
            stk.append(i % size)
        return res

print(Solution().nextGreaterElements([1,2,3,4,3]))
