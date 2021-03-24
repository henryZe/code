from typing import List

class Solution:
    # 1 time O((m + n)log(m + n))
    # def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
    #     nums1.extend(nums2)
    #     nums1.sort()
    #     n = len(nums1)
    #     if n % 2:
    #         return nums1[n // 2]
    #     else:
    #         return (nums1[n // 2 - 1] + nums1[n // 2]) / 2

    # 2 merge order method: time O(m + n)

    # 3 time O(log(min(m, n)))
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        if len(nums1) > len(nums2):
            tmp = nums1
            nums1 = nums2
            nums2 = tmp

        m = len(nums1)
        n = len(nums2)
        # right position
        total_left = (m + n + 1) // 2

        # 在 nums1 的区间 [0, m] 里查找恰当的分割线
        # nums1[i - 1] <= nums2[j]
        left = 0
        right = m

        while left < right:
            i = (left + right + 1) // 2
            j = total_left - i
            if nums1[i - 1] > nums2[j]:
                right = i - 1
            else:
                left = i

        i = left
        j = total_left - i
        nums1LeftMax = float("-inf") if i == 0 else nums1[i - 1]
        nums1RightMin = float("inf") if i == m else nums1[i]
        nums2LeftMax = float("-inf") if j == 0 else nums2[j - 1]
        nums2RightMin = float("inf") if j == n else nums2[j]

        if ((m + n) % 2) == 1:
            return max(nums1LeftMax, nums2LeftMax)
        else:
            return (max(nums1LeftMax, nums2LeftMax) + min(nums1RightMin, nums2RightMin)) / 2

# nums1 = [1,3]
# nums2 = [2]
nums1 = [1,2]
nums2 = [3,4]
# nums1 = [0,0]
# nums2 = [0,0]
# nums1 = []
# nums2 = [1]
# nums1 = [2]
# nums2 = []
print(Solution().findMedianSortedArrays(nums1, nums2))
