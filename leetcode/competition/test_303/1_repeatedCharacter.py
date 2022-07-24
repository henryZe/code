class Solution:
    def repeatedCharacter(self, s: str) -> str:
        set_c = set()

        for c in s:
            if c not in set_c:
                set_c.add(c)
            else:
                return c

        return None


s = "abccbaacz"
# s = "abcdd"
print(Solution().repeatedCharacter(s))
