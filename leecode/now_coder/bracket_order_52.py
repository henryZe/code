class Solution:
    def isValid(self , s ):
        stack = []
        ref = {
            "}": "{",
            "]": "[",
            ")": "("
        }

        for c in s:
            if c in ref.values():
                stack.append(c)
            else:
                if c in ref.keys():
                    if len(stack) == 0:
                        return False
                    if stack.pop() != ref[c]:
                        return False

        return len(stack) == 0


print(Solution().isValid("()"))
