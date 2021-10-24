from typing import List

class Solution:
    # def sortedSquares(self, nums: List[int]) -> List[int]:
    #     n = len(nums)
    #     for i in range(n):
    #         nums[i] *= nums[i]

    #     nums.sort()
    #     return nums

    def sortedSquares(self, nums: List[int]) -> List[int]:
        n = len(nums)
        neg_pos = -1
        for i, num in enumerate(nums):
            if num < 0:
                neg_pos = i
            else:
                break

        ans = []
        i, j = neg_pos, neg_pos + 1
        while i >= 0 or j < n:
            if i < 0:
                ans.append(nums[j] * nums[j])
                j += 1
            elif j >= n:
                ans.append(nums[i] * nums[i])
                i -= 1

            elif nums[i] * nums[i] < nums[j] * nums[j]:
                ans.append(nums[i] * nums[i])
                i -= 1
            else:
                ans.append(nums[j] * nums[j])
                j += 1

        return ans

# nums = [-4,-1,0,3,10]
nums = [-7,-3,2,3,11]
print(Solution().sortedSquares(nums))
