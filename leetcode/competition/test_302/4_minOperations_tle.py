from typing import List

def exam(numsDivide: List[int], n):
    for d in numsDivide:
        if d % n:
            return False
    return True

class Solution:
    def minOperations(self, nums: List[int], numsDivide: List[int]) -> int:
        nums.sort()
        d_count = 0
        while nums:
            if exam(numsDivide, nums[0]):
                break

            n = nums[0]
            while nums and nums[0] == n:
                nums.pop(0)
                d_count += 1
            
        if not nums:
            return -1
        return d_count


# nums = [2,3,2,4,3]
# numsDivide = [9,6,9,3,15]
nums = [4,3,6]
numsDivide = [8,2,6,10]
print(Solution().minOperations(nums, numsDivide))
