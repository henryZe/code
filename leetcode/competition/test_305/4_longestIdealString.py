class Solution:
    # O(n * 2k)
    def longestIdealString(self, s: str, k: int) -> int:
        dp = [0] * 26
        for c in s:
            c = ord(c) - ord('a')
            dp[c] = max(dp[max(c - k, 0): min(c + k + 1, 26)]) + 1

        return max(dp)

# s = "acfgbd"
# k = 2
s = "abcd"
k = 3
print(Solution().longestIdealString(s, k))
