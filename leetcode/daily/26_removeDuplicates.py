from typing import List

class Solution:
    # double pointers
    def removeDuplicates(self, nums: List[int]) -> int:
        if not nums:
            return 0

        n = len(nums)
        pos = 0
        for i in range(1, n):
            if nums[i] != nums[i - 1]:
                pos += 1
                nums[pos] = nums[i]

        return pos + 1

nums = [1,1,2]
num = Solution().removeDuplicates(nums)
for i in range(num):
    print(nums[i])