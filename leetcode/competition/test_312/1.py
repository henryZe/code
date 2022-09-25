from typing import List

class Solution:
    def sortPeople(self, names: List[str], heights: List[int]) -> List[str]:
        idx = []
        for i, h in enumerate(heights):
                idx.append([h, i])
        idx.sort(reverse=True)

        res = []
        for _, i in idx:
                res.append(names[i])
        return res


names = ["Mary","John","Emma"]
heights = [180,165,170]
print(Solution().sortPeople(names, heights))