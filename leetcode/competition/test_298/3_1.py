# 分类 + 贪心
# O(n)
class Solution:
    def longestSubsequence(self, s: str, k: int) -> int:
        len_s = len(s)
        len_k = k.bit_length()

        if len_s < len_k:
            return len_s

        ans = len_k
        if int(s[len_s - len_k:], 2) > k:
            ans = len_k - 1
        else:
            ans = len_k

        return ans + s.count('0', 0, len_s - len_k)

s, k = "1001010", 5
print(Solution().longestSubsequence(s, k))
