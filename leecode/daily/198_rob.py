from typing import List

class Solution:
    def rob(self, nums: List[int]) -> int:
        size = len(nums)
        f = [0] * (size + 1)

        for i in range(1, size + 1):
            if i == 1:
                f[i] = nums[0]
            elif i == 2:
                f[i] = max(nums[0:2])
            else:
                f[i] = max(f[i - 2] + nums[i - 1], f[i - 1])

        # print(f)
        return f[-1]

nums = [2,3,2]
nums = [2,7,9,3,1]
nums = [1,2,3,1]
nums = [1,2]
print(Solution().rob(nums))
