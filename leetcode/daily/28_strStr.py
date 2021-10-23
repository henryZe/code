from typing import List

class Solution:
    # TYTS
    # O(n * m)
    # def strStr(self, haystack: str, needle: str) -> int:
    #     if not needle:
    #         return 0
    # 
    #     if not haystack:
    #         return -1
    # 
    #     m = len(haystack)
    #     n = len(needle)
    #     res = -1
    #     for i in range(len(haystack)):
    #         if haystack[i: i + n] == needle:
    #             res = i
    #             break
    # 
    #     return res

    # Knuth-Morris-Pratt KMP 算法
    # time O(n+m)
    # space O(m)
    def strStr(self, haystack: str, needle: str) -> int:

        # time O(m) = O(m * k), k < m
        def partialMatchTable(pattern: str) -> List[int]:
            length = len(pattern)
            pmt = [0] * length

            for i in range(1, length):
                k = pmt[i - 1]
                while k > 0 and pattern[i] != pattern[k]:
                    k = pmt[k - 1]
                if pattern[i] == pattern[k]:
                    pmt[i] = k + 1

            return pmt

        n = len(haystack)
        m = len(needle)

        if not needle:
            return 0

        if n < m:
            return -1

        pmt = partialMatchTable(needle)
        i = j = 0
        while i < n:
            if haystack[i] == needle[j]:
                if j == m - 1:
                    # finish
                    return i - j
                i += 1
                j += 1

            else:
                if j > 0:
                    j = pmt[j - 1]
                else:
                    i += 1

        return -1

# haystack = "hello"
# needle = "ll"
# haystack = "aaaaa"
# needle = "bba"
# haystack = ""
# needle = ""
haystack = "mississippi"
needle = "issipi"
print(Solution().strStr(haystack, needle))