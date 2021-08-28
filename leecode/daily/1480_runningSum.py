from typing import List

class Solution:
    def runningSum(self, nums: List[int]) -> List[int]:
        array = []
        sum = 0

        for i in range(len(nums)):
            sum += nums[i]
            array.append(sum)

        return array

print(Solution().runningSum([1, 2, 3, 4, 5]))
