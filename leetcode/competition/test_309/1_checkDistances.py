from typing import List

class Solution:
    def checkDistances(self, s: str, distance: List[int]) -> bool:
        h = {}
        for i, c in enumerate(s):
            if c not in h:
                h[c] = i
            else:
                h[c] = i - h[c] - 1

        for k, v in h.items():
            index = ord(k) - ord('a')
            if distance[index] != v:
                return False
        return True

s = "abaccb"
distance = [1,3,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
print(Solution().checkDistances(s, distance))
