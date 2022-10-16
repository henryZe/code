from typing import List

class Solution:
    def findMaxK(self, nums: List[int]) -> int:
        cur_max = -1
        h_neg = set()
        h = set()
        for num in nums:
            if num > 0:
                if num in h:
                    cur_max = max(cur_max, num)
                else:
                    h_neg.add(-num)
            else:
                if num in h_neg:
                    cur_max = max(cur_max, -num)
                else:
                    h.add(-num)

        return cur_max

# nums = [-1,2,-3,3]
# nums = [-1,10,6,7,-7,1]
nums = [-10,8,6,7,-2,-3]
print(Solution().findMaxK(nums))
