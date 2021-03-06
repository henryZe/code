from typing import List
import bisect

# O(n * logn)
class Solution:
    def countSmaller(self, nums: List[int]) -> List[int]:
        if not nums:
            return []

        size = len(nums)
        counts = [0] * size
        ordered = []

        for i in range(size - 1, -1, -1):
            counts[i] = bisect.bisect_left(ordered, nums[i])
            ordered.insert(counts[i], nums[i])

        return counts


nums = [5,2,6,1]
# nums = [-1,-1]
print(Solution().countSmaller(nums))
