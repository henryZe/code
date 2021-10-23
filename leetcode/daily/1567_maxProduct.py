from typing import List

class Solution:
    def getMaxLen(self, nums: List[int]) -> int:
        n = len(nums)
        left, right = 0, 0
        neg = 0
        max_len = 0

        # double pointer
        while left < n:
            # find right pos of subarray
            while right < n and nums[right] != 0:
                if nums[right] < 0:
                    neg += 1
                right += 1
                if neg % 2 == 0:
                    max_len = max(max_len, right - left)

            if neg % 2 == 1:
                while left < right:
                    if nums[left] < 0:
                        neg -= 1
                    left += 1
                    if neg % 2 == 0:
                        max_len = max(max_len, right - left)

            if right >= n:
                break

            if nums[right] == 0:
                right += 1
            left = right
            neg = 0

        return max_len

# nums = [1,-2,-3,4]
# nums = [-1,2]
nums = [0,1,-2,-3,-4]
print(Solution().getMaxLen(nums))
