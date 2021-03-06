from typing import List

class Solution:
    def isMonotonic(self, A: List[int]) -> bool:
        inc = True
        dec = True

        for i in range(0, len(A) - 1):
            if A[i] > A[i + 1]:
                inc = False

            elif A[i] < A[i + 1]:
                dec = False

        return inc or dec

print(Solution().isMonotonic([1,2,4,5]))