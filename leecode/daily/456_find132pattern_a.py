from typing import List
# import bisect
from sortedcontainers import SortedList

class Solution:
    # time O(n*logn + n*(logn + n)) = O(n^2)
    # space O(n)
    # def find132pattern(self, nums: List[int]) -> bool:
    #     n = len(nums)
    #     left_min = nums[0]
    #     right_all = nums[2::]
    #     right_all.sort()
    # 
    #     for i in range(1, n - 1):
    #         index = bisect.bisect_right(right_all, left_min)
    #         if index < len(right_all) and right_all[index] < nums[i]:
    #             return True
    # 
    #         left_min = min(left_min, nums[i])
    #         right_all.remove(nums[i + 1])
    # 
    #     return False

    # time O(n*logn + n*(logn + logn)) = O(n*logn)
    # space O(n)
    def find132pattern(self, nums: List[int]) -> bool:
        n = len(nums)
        left_min = nums[0]
        right_all = SortedList(nums[2::])

        for i in range(1, n - 1):
            index = right_all.bisect_right(left_min)
            if index < len(right_all) and right_all[index] < nums[i]:
                return True

            left_min = min(left_min, nums[i])
            right_all.remove(nums[i + 1])

        return False


# nums = [1,2,3,4]
# nums = [3,1,4,2]
nums = [-1,3,2,0]
print(Solution().find132pattern(nums))
