from typing import List

class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        nums1.extend(nums2)
        nums1.sort()
        n = len(nums1)
        if n % 2:
            return nums1[n // 2]
        else:
            return (nums1[n // 2 - 1] + nums1[n // 2]) / 2

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
