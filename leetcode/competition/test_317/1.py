from typing import List

class Solution:
    def averageValue(self, nums: List[int]) -> int:
        l = []
        for num in nums:
            if num % 6 == 0:
                l.append(num)

        if not l:
            return 0
        return sum(l) // len(l)


nums = [1,3,6,10,12,15]
# nums = [1,2,4,7,10]
print(Solution().averageValue(nums))
