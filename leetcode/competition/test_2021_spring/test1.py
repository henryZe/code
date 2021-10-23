from typing import List

class Solution:
    # O(n * logn)
    def purchasePlans(self, nums: List[int], target: int) -> int:
        if not nums:
            return 0

        nums.sort()
        ans = 0
        stack = []

        for num in nums:
            if num > target:
                break
            
            meet = target - num
            while stack and meet < stack[-1]:
                stack.pop()
            ans += len(stack)
            stack.append(num)

        return ans % 1000000007

# nums = [2,5,3,5]
# target = 6
# nums = [2,2,1,9]
# target = 10
nums = [2,5,3,5]
target = 6
print(Solution().purchasePlans(nums, target))