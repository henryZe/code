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
        if not needle:
            return 0
    
        if not haystack:
            return -1

        n = len(haystack)
        m = len(needle)

        return True

# haystack = "hello"
# needle = "ll"
# haystack = "aaaaa"
# needle = "bba"
haystack = ""
needle = ""
print(Solution().strStr(haystack, needle))