from typing import List

class Solution:
    # double pointers
    def removeDuplicates(self, nums: List[int]) -> int:
        if not nums:
            return 0

        n = len(nums)
        slow, fast = 2, 2
        while fast < n:
            if nums[slow - 2] != nums[fast]:
                nums[slow] = nums[fast]
                slow += 1
            fast += 1

        return slow

nums = [1,1,1,2,2,3]
num = Solution().removeDuplicates(nums)
for i in range(num):
    print(nums[i])