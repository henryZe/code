from typing import List

class Solution:
    def longestContinuousSubstring(self, s: str) -> int:
        ref = "abcdefghijklmnopqrstuvwxyz"
        res = 0

        cur = 1
        idx = 1
        ref_i = ord(s[0]) - ord('a') + 1
        while idx < len(s):
            if ref_i >= 26 or ref[ref_i] != s[idx]:
                ref_i = ord(s[idx]) - ord('a') + 1
                res = max(res, cur)
                cur = 1
            else:
                ref_i += 1
                cur += 1
            idx += 1

        return max(res, cur)

# s = "abacaba"
# s = "abcde"
# s = "z"
s = "abcabcda"
print(Solution().longestContinuousSubstring(s))
