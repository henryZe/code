from typing import List
import bisect

class Solution:
    def find132pattern(self, nums: List[int]) -> bool:
        n = len(nums)
        left_min = nums[0]
        right_all = nums[2::]
        right_all.sort()

        for i in range(1, n - 1):
            index = bisect.bisect_right(right_all, left_min)
            if index < len(right_all) and right_all[index] < nums[i]:
                return True

            left_min = min(left_min, nums[i])
            right_all.remove(nums[i + 1])

        return False


# nums = [1,2,3,4]
# nums = [3,1,4,2]
nums = [-1,3,2,0]
print(Solution().find132pattern(nums))
