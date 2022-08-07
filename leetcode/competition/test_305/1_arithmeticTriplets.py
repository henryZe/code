from typing import List

class Solution:
    def arithmeticTriplets(self, nums: List[int], diff: int) -> int:
        count = 0
        nums = set(nums)
        for x in nums:
            if x - diff in nums and x + diff in nums:
                count += 1

        return count

nums = [0,1,4,6,7,10]
diff = 3
# nums = [4,5,6,7,8,9]
# diff = 2
print(Solution().arithmeticTriplets(nums, diff))
