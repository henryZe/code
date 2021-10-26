class Solution:
    def reverseWords(self, s: str) -> str:
        l = s.split(' ')
        # print(l)
        res = []
        for m in l:
            res.append(m[::-1])
        return " ".join(res)


s = "Let's take LeetCode contest"
print(Solution().reverseWords(s))
