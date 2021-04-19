from typing import List

class Solution:
    # TYTS
    # time O(n * k)
    # space O(1)
    # def containsNearbyAlmostDuplicate(self, nums: List[int], k: int, t: int) -> bool:
    #     n = len(nums)
    #     for i in range(n):
    #         for j in range(i - k, i + k + 1):
    #             if j in range(n) and i != j:
    #                 if abs(nums[i] - nums[j]) <= t:
    #                     # print(i, j)
    #                     return True
    #     return False

    # 桶排序
    # time O(n)
    # space O(min(n, k))
    def containsNearbyAlmostDuplicate(self, nums: List[int], k: int, t: int) -> bool:
        all_buckets = {}
        bucket_size = t + 1

        for i in range(len(nums)):
            bucket = nums[i] // bucket_size

            if bucket in all_buckets:
                return True

            all_buckets[bucket] = nums[i]

            if (bucket - 1) in all_buckets and abs(all_buckets[bucket - 1] - nums[i]) <= t:
                return True

            if (bucket + 1) in all_buckets and abs(all_buckets[bucket + 1] - nums[i]) <= t:
                return True

            if i >= k:
                all_buckets.pop(nums[i - k] // bucket_size)

        return False


# nums = [1,2,3,1]
# k = 3
# t = 0
nums = [1,5,9,1,5,9]
k = 2
t = 3
print(Solution().containsNearbyAlmostDuplicate(nums, k, t))