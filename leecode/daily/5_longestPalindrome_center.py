class Solution:
    # center-expand search
    def longestPalindrome(self, s: str) -> str:
        def calculate_len(s: str, left: int, right: int) -> int:
            while left >= 0 and right < len(s):
                if s[left] != s[right]:
                    break
                left -= 1
                right += 1
            return right - left - 1

        n = len(s)
        max_len = 1
        new = 0
        for i in range(n):
            odd_len = calculate_len(s, i, i)
            even_len = calculate_len(s, i, i + 1)

            cur_len = max(odd_len, even_len)
            if max_len < cur_len:
                new = i - (cur_len - 1) // 2
                max_len = cur_len

        return s[new : new + max_len]

print(Solution().longestPalindrome("babad"))
print(Solution().longestPalindrome("cbbd"))
