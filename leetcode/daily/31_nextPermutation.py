from typing import List

class Solution:
    def nextPermutation(self, nums: List[int]) -> None:
        i = len(nums) - 2
        while i >= 0 and nums[i] >= nums[i + 1]:
            i -= 1
        if i >= 0:
            j = len(nums) - 1
            while j >= 0 and nums[i] >= nums[j]:
                j -= 1
            # exchange the min num with the closest bigger one
            nums[i], nums[j] = nums[j], nums[i]

        # reverse the rest
        left, right = i + 1, len(nums) - 1
        while left < right:
            nums[left], nums[right] = nums[right], nums[left]
            left += 1
            right -= 1

        return

# nums = [1,2,3]
# nums = [3,2,1]
# nums = [1,1,5]
# nums = [1]
nums = [5,1,1]
Solution().nextPermutation(nums)
print(nums)