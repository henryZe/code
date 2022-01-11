from typing import List

class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        res = []

        def backtrack(lstack, rstack, times):
            if not rstack and times >= n:
                res.append("".join(lstack))
                return

            if rstack:
                lstack.append(rstack.pop())
                backtrack(lstack, rstack, times)
                rstack.append(lstack.pop())

            if times < n:
                lstack.append("(")
                rstack.append(")")
                backtrack(lstack, rstack, times + 1)
                lstack.pop()
                rstack.pop()

            return

        backtrack([], [], 0)
        return res

n = 1
n = 3
print(Solution().generateParenthesis(n))
