from typing import List

class Solution:
    # 迭代法实现子集枚举
    # def subsets(self, nums: List[int]) -> List[List[int]]:
    #     ans = []
    #     n = len(nums)
    # 
    #     for mask in range(1 << n):
    #         tmp = []
    #         for i in range(n):
    #             if mask & (1 << i):
    #                 tmp.append(nums[i])
    #         ans.append(tmp)
    # 
    #     return ans

    # 递归法实现子集枚举
    def subsets(self, nums: List[int]) -> List[List[int]]:

        def dfs(pos: int):
            if pos == len(nums):
                ans.append(tmp[::])
                return

            tmp.append(nums[pos])
            dfs(pos + 1)
            tmp.pop()
            dfs(pos + 1)
            return

        ans = []
        tmp = []
        dfs(0)
        return ans

nums = [1,2,3]
print(Solution().subsets(nums))
