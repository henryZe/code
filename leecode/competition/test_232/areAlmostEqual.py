
class Solution:
    def areAlmostEqual(self, s1: str, s2: str) -> bool:
        diff = 0
        n = len(s1)
        index = 0
        for i in range(n):
            if s1[i] != s2[i]:
                if diff == 0:
                    index = i
                    diff += 1
                elif diff == 1:
                    if s1[index] == s2[i] and s2[i] == s1[index]:
                        diff += 1
                    else:
                        return False
                else:
                    return False

        return False if diff == 1 else True

s1 = "bank"
s2 = "kanb"

s1 = "attack"
s2 = "defend"

s1 = "kelb"
s2 = "kelb"

s1 = "abcd"
s2 = "dcba"
print(Solution().areAlmostEqual(s1, s2))