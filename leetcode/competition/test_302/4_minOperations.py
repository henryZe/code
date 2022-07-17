from typing import List
import math

class Solution:
    def minOperations(self, nums: List[int], numsDivide: List[int]) -> int:
        target = numsDivide[0]
        for i in numsDivide[1:]:
            target = math.gcd(target, i)

        nums.sort()
        for i, num in enumerate(nums):
            if target % num == 0:
                return i

        return -1


# nums = [2,3,2,4,3]
# numsDivide = [9,6,9,3,15]
nums = [4,3,6]
numsDivide = [8,2,6,10]
print(Solution().minOperations(nums, numsDivide))
