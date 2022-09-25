from typing import List

class Solution:
    def longestSubarray(self, nums: List[int]) -> int:
        n = len(nums)
        cur_max = nums[0]
        len_max = 1
        cur_len = 1
        for i in range(1, n):
            if nums[i] < cur_max:
                cur_len = 0
            elif nums[i] == cur_max:
                cur_len += 1
                len_max = max(len_max, cur_len)
            else:
                cur_max = nums[i]
                cur_len = 1
                len_max = cur_len

        return len_max

nums = [1,2,3,3,2,2]
# nums = [1,2,3,4]
print(Solution().longestSubarray(nums))
