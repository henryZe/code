from bisect import bisect
from typing import List
import bisect

class Solution:
    def answerQueries(self, nums: List[int], queries: List[int]) -> List[int]:
        nums.sort()
        n = len(nums)
        pre = [nums[0]] * n
        for i, num in enumerate(nums):
            if i > 0:
                pre[i] = pre[i - 1] + num

        res = [0] * len(queries)
        for i, item in enumerate(queries):
            pos = bisect.bisect(pre, item)
            res[i] = pos

        return res

nums = [4,5,2,1]
queries = [3,10,21]
# nums = [2,3,4,5]
# queries = [1]
print(Solution().answerQueries(nums, queries))
