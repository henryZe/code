from typing import List

class Solution:
    def searchInsert(self, nums: List[int], target: int) -> int:
        l = 0
        r = len(nums) - 1

        while l <= r:
            mid = (l + r) // 2
            # print(mid, nums[mid])

            if nums[mid] == target:
                return mid

            if nums[mid] < target:
                l = mid + 1
            else:
                r = mid - 1

        return l

# nums = [1,3,5,6]
# target = 5
nums = [1,3,5,6]
target = 2
print(Solution().searchInsert(nums, target))
