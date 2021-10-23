from typing import List

class Solution:
    def merge(self, nums1: List[int], m: int, nums2: List[int], n: int) -> None:
        if not n:
            return

        i, j = 0, 0
        while j < n:
            # nums1 is over
            if i >= m + j:
                nums1[i] = nums2[j]
                j += 1
            elif nums1[i] > nums2[j]:
                # reserve a space for nums2
                for k in range(m + j, i, -1):
                    nums1[k] = nums1[k - 1]
                # fill it
                nums1[i] = nums2[j]
                j += 1
            i += 1
        return

# nums1 = [1,2,3,0,0,0]
# m = 3
# nums2 = [2,5,6]
# n = 3
nums1 = [1]
m = 1
nums2 = []
n = 0
Solution().merge(nums1, m, nums2, n)
print(nums1)