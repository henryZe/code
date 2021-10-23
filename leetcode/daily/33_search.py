from typing import List

class Solution:
    # O(logn)
    def search(self, nums: List[int], target: int) -> int:
        if not nums:
            return -1

        n = len(nums)
        l = 0
        r = n - 1
        while l <= r:
            mid = (l + r) // 2
            if target == nums[mid]:
                return mid

            # [0:mid] is ordered
            if nums[0] < nums[mid]:
                if nums[0] <= target < nums[mid]:
                    r = mid - 1
                else:
                    l = mid + 1
            # [mid:n - 1] is ordered
            else:
                if nums[mid] < target <= nums[n - 1]:
                    l = mid + 1
                else:
                    r = mid - 1

        return -1

nums = [4,5,6,7,0,1,2]
target = 0
# nums = [4,5,6,7,0,1,2]
# target = 3
# nums = [1]
# target = 0
print(Solution().search(nums, target))