from typing import Counter, List

class Solution:
    def majorityElement(self, nums: List[int]) -> List[int]:
        n = len(nums)
        d = Counter(nums)

        l = []
        for key, value in d.items():
            if value >= (n // 3 + 1):
                l.append(key)
        return l

# nums = [3,2,3]
# nums = [1]
nums = [1,1,1,3,3,2,2,2]
print(Solution().majorityElement(nums))
