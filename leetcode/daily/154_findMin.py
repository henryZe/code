from typing import List

class Solution:
    def findMin(self, nums: List[int]) -> int:
        l = 0
        r = len(nums) - 1
        while l < r:
            mid = (l + r) // 2

            # O(log n)
            if nums[mid] < nums[r]:
                r = mid
            elif nums[mid] > nums[r]:
                l = mid + 1
            # O(n)
            elif nums[mid] == nums[r]:
                r -= 1
        return nums[l]

nums = [1,3,5]
nums = [2,2,2,0,1]
nums = [1,3,3]
print(Solution().findMin(nums))