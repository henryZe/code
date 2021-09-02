from typing import List

class Solution:
    # backtracking
    def canJump(self, nums: List[int]) -> bool:
        def check(pos: int) -> bool:
            if pos == len(nums) - 1:
                return True

            step = nums[pos]
            ret = False
            for i in range(1, step + 1):
                if dp[pos + i] == True:
                    ret = check(pos + i)
                    if ret == True:
                        break
                    else:
                        dp[pos + i] = False
            return ret
        
        dp = [True] * len(nums)
        return check(0)

# nums = [2,3,1,1,4]
nums = [3,2,1,0,4]
print(Solution().canJump(nums))