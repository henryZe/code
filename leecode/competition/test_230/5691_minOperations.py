class Solution:
    def minOperations(self, nums1: List[int], nums2: List[int]) -> int:
        len1 = len(nums1)
        len2 = len(nums2)

        if abs(len1 - len2) > 5:
            return -1

        res = 0



        return res

nums1 = [1,2,3,4,5,6]
nums2 = [1,1,2,2,2,2]
# nums1 = [1,1,1,1,1,1,1]
# nums2 = [6]
# nums1 = [6,6]
# nums2 = [1]
print(Solution().minOperations(nums1, nums2))
