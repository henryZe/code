from typing import List

class Solution:
    def minElements(self, nums: List[int], limit: int, goal: int) -> int:
        sumNums = sum(nums)
        delta = abs(sumNums - goal)

        if not delta:
            return 0
        if delta % limit:
            return delta // limit + 1
        return delta // limit

# nums = [1,-1,1]
# limit = 3
# goal = -4
# nums = [1,-10,9,1]
# limit = 100
# goal = 0
nums = [-1,0,1,1,1]
limit = 1
goal = 771843707

res = Solution().minElements(nums, limit, goal)
print(res)