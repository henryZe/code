from typing import List

class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        size = len(nums)
        maxF = [0] * size
        minF = [0] * size
        maxF[0] = minF[0] = nums[0]

        for i in range(1, size):
            maxF[i] = max(maxF[i - 1] * nums[i], minF[i - 1] * nums[i], nums[i])
            minF[i] = min(maxF[i - 1] * nums[i], minF[i - 1] * nums[i], nums[i])

        return max(maxF)


print(Solution().maxProduct([-2,3,-4]))
