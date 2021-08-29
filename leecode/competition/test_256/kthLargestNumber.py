from typing import List

class Solution:
    def kthLargestNumber(self, nums: List[str], k: int) -> str:
        l = []

        for num in nums:
            l.append(int(num))

        l.sort(reverse=True)
        return str(l[k - 1])

print(Solution().kthLargestNumber(["3","6","7","10"], 4))
print(Solution().kthLargestNumber(["2","21","12","1"], 3))
print(Solution().kthLargestNumber(["0","0"], 2))
