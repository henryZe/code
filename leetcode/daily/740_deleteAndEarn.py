from typing import List

class Solution:
    def deleteAndEarn(self, nums: List[int]) -> int:
        maxVal = max(nums)
        hash = [0] * (maxVal + 1)

        for val in nums:
            hash[val] += val

        def rob(hash: List[int]):
            size = len(hash)

            if size == 2:
                return hash[1]
            elif size == 3:
                return max(hash[1], hash[2]) 

            first, second = hash[1], max(hash[1], hash[2])
            for i in range(3, size):
                first, second = second, max(first + hash[i], second)
            return second

        return rob(hash)

nums = [3,4,2]
nums = [1]
print(Solution().deleteAndEarn(nums))