from typing import List

class Solution:
    # O(n)
    def search(self, nums: List[int], target: int) -> bool:
        if not nums:
            return False

        n = len(nums)
        l = 0
        r = n - 1
        while l <= r:
            mid = (l + r) // 2
            if target == nums[mid]:
                return True

            if nums[l] == nums[mid] and nums[r] == nums[mid]:
                l += 1
                r -= 1
            elif nums[l] <= nums[mid]:
                # [l:mid] is ordered
                if nums[l] <= target < nums[mid]:
                    r = mid - 1
                else:
                    l = mid + 1
            else:
                # [mid:r] is ordered
                if nums[mid] < target <= nums[r]:
                    l = mid + 1
                else:
                    r = mid - 1
        return False

# nums = [2,5,6,0,0,1,2]
# target = 0
# nums = [2,5,6,0,0,1,2]
# target = 3
nums = [1,1,1,1,1,1,1,1,1,13,1,1,1,1,1,1,1,1,1,1,1,1]
target = 13
print(Solution().search(nums, target))