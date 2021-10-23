class Solution:
    def calculate(self, s: str) -> int:
        i = 0
        n = len(s)
        num = 0
        stack = []
        preSign = "+"
 
        def opt(preSign: str, num: int):
            if preSign == "+":
                stack.append(num)
            elif preSign == "-":
                stack.append(-num)
            elif preSign == "*":
                stack.append(stack.pop() * num)
            elif preSign == "/":
                if stack[-1] < 0:
                    stack.append(-(-stack.pop() // num))
                else:
                    stack.append(stack.pop() // num)
            return

        while i < n:
            if s[i].isdigit():
                num = num * 10 + int(s[i])
            elif s[i] == " ":
                pass
            else:
                opt(preSign, num)
                preSign = s[i]
                num = 0
            i += 1

        # last time calculate
        opt(preSign, num)
        return sum(stack)

s = "14-3/2"
print(Solution().calculate(s))
