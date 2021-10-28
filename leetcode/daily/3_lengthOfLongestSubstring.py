# class Solution:
#     # T(n) = O(n^2)
#     def lengthOfLongestSubstring(self, s: str) -> int:
#         begin = 0
#         n = len(s)
#         ret = 0

#         for end in range(n):
#             for i in range(begin, end):
#                 if s[i] == s[end]:
#                     ret = max(ret, end - begin)
#                     begin += 1
#                     break
        
#         return max(ret, n - begin)

class Solution:
    # T(n) = O(n)
    def lengthOfLongestSubstring(self, s: str) -> int:
        begin = 0
        n = len(s)
        cset = set()
        ret = 0

        for end in range(n):
            while s[end] in cset:
                ret = max(ret, len(cset))
                cset.remove(s[begin])
                begin += 1

            cset.add(s[end])

        return max(ret, len(cset))

# s = "abcabcbb"
# s = "bbbbb"
# s = "pwwkew"
# s = ""
# s = " "
# s = "abba"
s = "aa"
print(Solution().lengthOfLongestSubstring(s))