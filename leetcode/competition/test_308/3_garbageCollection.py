from typing import List
from collections import Counter

class Solution:
    def garbageCollection(self, garbage: List[str], travel: List[int]) -> int:
        trash = ["M", "P", "G"]
        h = []
        for g in garbage:
            h.append(Counter(g))

        res = 0
        for t in trash:
            ptrash = 0
            start = 0
            for i, hitem in enumerate(h):
                ptime = 0
                if t in hitem:
                    ptime += sum(travel[start:i])
                    start = i

                    ptime += hitem[t]
                ptrash += ptime
            res += ptrash

        return res

# garbage = ["G","P","GP","GG"]
# travel = [2,4,3]
garbage = ["MMM","PGM","GP"]
travel = [3,10]
print(Solution().garbageCollection(garbage, travel))
