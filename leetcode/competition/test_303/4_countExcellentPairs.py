from typing import List

class Solution:
    def countExcellentPairs(self, nums: List[int], k: int) -> int:
        s_num = set(nums)
        h_countbit = {}
        for num in s_num:
            c = bin(num).count("1")
            if c not in h_countbit:
                h_countbit[c] = 1
            else:
                h_countbit[c] += 1

        count = 0
        for x, cx in h_countbit.items():
            for y, cy in h_countbit.items():
                if x + y >= k:
                    count += cx * cy

        return count

# nums = [1,2,3,1]
# k = 3
nums = [5,1,1]
k = 10
print(Solution().countExcellentPairs(nums, k))