from typing import List

# 计算复杂度 O(n ^ 2)
# 双指针算法
class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        # O(n * log n)
        nums.sort()
        n = len(nums)
        ret = []

        if n < 3:
            return ret

        for i in range(n):
            # 需要和上一次枚举的数不相同
            if i > 0 and nums[i] == nums[i - 1]:
                continue

            target = -nums[i]
            k = n - 1
            for j in range(i + 1, n):
                # 需要和上一次枚举的数不相同
                if j > i + 1 and nums[j] == nums[j - 1]:
                    continue

                # second & third 相向而行
                while nums[j] + nums[k] > target and k > j:
                    k -= 1

                # not meet
                if j == k:
                    break

                # meet
                if nums[j] + nums[k] == target:
                    ret.append([nums[i], nums[j], nums[k]])

        return ret

nums = [-1,0,1,2,-1,-4]
print(Solution().threeSum(nums))
