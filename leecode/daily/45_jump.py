from typing import List

class Solution:
    def jump(self, nums: List[int]) -> int:
        n = len(nums)
        pos = n - 1
        step = 0

        while pos:
            for j in range(0, n):
                if nums[j] + j >= pos:
                    pos = j
                    step += 1
                    break

        return step

nums = [2,3,1,1,4]
nums = [2,3,0,1,4]
print(Solution().jump(nums))
