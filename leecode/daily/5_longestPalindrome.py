
class Solution:
    # exhausted search
    def longestPalindrome(self, s: str) -> str:
        n = len(s)
        max_len = 1
        new = 0
        for i in range(n):
            for j in range(i + 1, n):
                if s[i] == s[j]:
                    start = i
                    end = j
                    res = True
                    while start < end:
                        start += 1
                        end -= 1
                        if s[start] != s[end]:
                            res = False
                            break

                    if res == True:
                        length = j - i + 1
                        if max_len < length:
                            max_len = length
                            new = i

        newstr = s[new : new + max_len]        
        return newstr

print(Solution().longestPalindrome("cbbd"))
