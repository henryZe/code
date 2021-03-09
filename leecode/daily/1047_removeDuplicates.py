class Solution:
    def removeDuplicates(self, S: str) -> str:
        stack = []
        for c in S:
            if stack:
                if stack[-1] == c:
                    stack.pop()
                    continue

            stack.append(c)
        return "".join(stack)

s = "abbaca"
print(Solution().removeDuplicates(s))
