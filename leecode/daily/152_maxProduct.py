from typing import List

class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        n = len(nums)

        cur_max = nums[0]
        cur_min = nums[0]
        ret = cur_max

        for i in range(1, n):
            if nums[i] > 0:
                cur_max = max(nums[i] * cur_max, nums[i])
                cur_min = min(nums[i] * cur_min, nums[i])

            else:
                temp = max(nums[i] * cur_min, nums[i])
                cur_min = min(nums[i] * cur_max, nums[i])
                cur_max = temp

            ret = max(cur_max, ret)
            print(cur_max, cur_min, ret)

        # Time(n) = O(n)
        # Space(n) = O(1)
        return ret

nums = [
    [2,3,-2,4],
    [-2,0,-1],
    [0,2],
    [3,-1,4],
    [1,-2,-3,4],
    [-4,-3,-2],
]
for i in nums:
    print(Solution().maxProduct(i))
