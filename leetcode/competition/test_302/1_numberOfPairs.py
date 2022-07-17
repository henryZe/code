from typing import List

class Solution:
    def numberOfPairs(self, nums: List[int]) -> List[int]:
        s = set()
        count = 0
        for num in nums:
            if num not in s:
                s.add(num)
            else:
                count += 1
                s.remove(num)

        return [count, len(s)]


nums = [1,3,2,1,3,2,2]
print(Solution().numberOfPairs(nums))