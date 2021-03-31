from typing import List

class Solution:
    # 递归法
    def subsetsWithDup(self, nums: List[int]) -> List[List[int]]:
        def dfs(choosePre: bool, pos: int):
            if pos == len(nums):
                ans.append(tmp[::])
                return

            dfs(False, pos + 1)
            # 特例判别：
            # 1. 若发现没有选择上一个数，
            # 2. 且当前数字与上一个数相同，
            # 则可以跳过当前生成的子集
            if not choosePre and pos > 0 and nums[pos] == nums[pos - 1]:
                return

            tmp.append(nums[pos])
            dfs(True, pos + 1)
            tmp.pop()

            return

        ans = []
        tmp = []
        nums.sort()
        dfs(False, 0)
        return ans

nums = [1,2,2]
print(Solution().subsetsWithDup(nums))
