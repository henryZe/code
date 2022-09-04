from typing import List

class Solution:
    def longestNiceSubarray(self, nums: List[int]) -> int:
        left = 0
        right = 0
        res = 1
        l = len(nums)
        mask = nums[0]

        while (right + 1) < l:
            right += 1
            if mask & nums[right] == 0:
                mask |= nums[right]
                res = max(right - left + 1, res)
                continue

            while mask & nums[right]:
                mask &= ~nums[left]
                left += 1
            mask |= nums[right]

        return res

# nums = [1,3,8,48,10]
nums = [3,1,5,11,13]
print(Solution().longestNiceSubarray(nums))
