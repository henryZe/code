from typing import List

class Solution:
    def findArray(self, pref: List[int]) -> List[int]:
        n = len(pref)
        res = [pref[0]]

        for i in range(1, n):
            res.append(pref[i - 1] ^ pref[i])

        return res


pref = [5,2,0,3,1]
# pref = [13]
print(Solution().findArray(pref))
