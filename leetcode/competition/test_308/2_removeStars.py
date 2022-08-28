
class Solution:
    def removeStars(self, s: str) -> str:
        stack = []
        for c in s:
            if c != '*':
                stack.append(c)
            else:
                stack.pop()

        return "".join(stack)

s = "leet**cod*e"
print(Solution().removeStars(s))
