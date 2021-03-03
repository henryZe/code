from typing import Counter, List

# 贪心算法
class Solution:
    def minOperations(self, nums1: List[int], nums2: List[int]) -> int:
        sum1, sum2 = sum(nums1), sum(nums2)
        if sum1 == sum2:
            return 0
        if sum1 > sum2:
            return self.minOperations(nums2, nums1)

        diff = sum2 - sum1
        freq = Counter(6 - num for num in nums1) + Counter(num - 1 for num in nums2)
        res = 0

        for i in range(5, 0, -1):
            if diff <= 0:
                break
            for _ in range(freq[i]):
                if diff <= 0:
                    break
                diff -= i
                freq[i] -= 1
                res += 1

        return res if diff <= 0 else -1

nums1 = [1,2,3,4,5,6]
nums2 = [1,1,2,2,2,2]
# nums1 = [1,1,1,1,1,1,1]
# nums2 = [6]
# nums1 = [6,6]
# nums2 = [1]
print(Solution().minOperations(nums1, nums2))
