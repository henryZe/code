from typing import List

class Solution:
    # time O(n)
    # space O(n)
    def find132pattern(self, nums: List[int]) -> bool:
        n = len(nums)
        candidate_3 = [nums[n - 1]]
        max_2 = float("-inf")

        for i in range(n - 2, -1, -1):
            if nums[i] < max_2:
                return True

            while candidate_3 and nums[i] > candidate_3[-1]:
                max_2 = candidate_3.pop()

            if nums[i] > max_2:
                candidate_3.append(nums[i])

        return False


# nums = [1,2,3,4]
# nums = [3,1,4,2]
nums = [-1,3,2,0]
print(Solution().find132pattern(nums))
