from typing import List

class Solution:
    def minChanges(self, nums: List[int], k: int) -> int:
        res = 0

        if k == 1:
            for num in nums:
                if num:
                    res += 1
            return res
        
        for i in range(len(nums) - k + 1):
            target = nums[i]
            for num in nums[i+1:i+k-1]:
                target ^= num
            if target == nums[i + k - 1]:
                continue
            else:
                res += 1
                nums[i + k - 1] = target

        return res

# print(Solution().minChanges([1,2,0,3,0], 1))
# print(Solution().minChanges([3,4,5,2,1,7,3,4,7], 3))
# print(Solution().minChanges([1,2,4,1,2,5,1,2,6], 3))
print(Solution().minChanges([26,19,19,28,13,14,6,25,28,19,0,15,25,11], 3))
