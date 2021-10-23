from typing import List

class Solution:
    def rob(self, nums: List[int]) -> int:

        def rob_range(nums: List[int], start: int, end: int):
            f = [0] * len(nums)
            for i in range(start, end):
                if i == start:
                    f[i] = nums[start]
                elif i == start + 1:
                    f[i] = max(nums[start : start + 2])
                else:
                    f[i] = max(f[i - 2] + nums[i], f[i - 1])
            return f[end - 1]

        size = len(nums)
        if size == 1:
            return nums[0]

        return max(rob_range(nums, 0, size - 1), rob_range(nums, 1, size))

# nums = [2,3,2]
# nums = [2,7,9,3,1]
# nums = [1,2,3,1]
# nums = [1,2]
nums = [1]
print(Solution().rob(nums))
