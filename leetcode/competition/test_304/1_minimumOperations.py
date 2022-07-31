from typing import List
import heapq

class Solution:
    def minimumOperations(self, nums: List[int]) -> int:
        count = 0
        nums = list(set(nums))
        nums.sort()

        while nums:
            if nums[0] == 0:
                nums.pop(0)
                if not nums:
                    break

            min_num = nums.pop(0)
            for i in range(len(nums)):
                nums[i] = nums[i] - min_num
            count += 1

        return count


# nums = [1,5,0,3,5]
# nums = [0]
nums = [1]
print(Solution().minimumOperations(nums))
