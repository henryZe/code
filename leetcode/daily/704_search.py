from typing import List

class Solution:
    def search(self, nums: List[int], target: int) -> int:
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
        return -1

# nums = [-1,0,3,5,9,12]
# target = 9
# nums = [-1,0,3,5,9,12]
# target = 2
nums = [-1,0,3,5,9,12]
target = 13

print(Solution().search(nums, target))