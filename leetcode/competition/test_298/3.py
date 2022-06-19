# 贪心
# O(n^2)
class Solution:
    def longestSubsequence(self, s: str, k: int) -> int:
        s_len = len(s)
        cur_len = s_len

        for i in range(s_len):
            if int(s, 2) <= k:
                break
            if s[i] == '1':
                s = list(s)
                s[i] = '0'
                s = ''.join(s)
                cur_len -= 1

        return cur_len

s, k = "1001010", 5
print(Solution().longestSubsequence(s, k))
