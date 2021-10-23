class Solution:
    def calculate(self, s: str) -> int:
        n = len(s)
        i = 0

        opt = [1]
        sign = 1
        ret = 0

        while i < n:
            if s[i] == " ":
                i += 1
            elif s[i] == "+":
                sign = opt[-1]
                i += 1
            elif s[i] == "-":
                sign = -opt[-1]
                i += 1
            elif s[i] == "(":
                opt.append(sign)
                i += 1
            elif s[i] == ")":
                opt.pop()
                i += 1
            else:
                num = 0
                while i < n and s[i].isdigit():
                    num = num * 10 + int(s[i])
                    i += 1
                ret += num * sign
        return ret

s = "(1+(4+5+2)-3)+(6+8)"
print(Solution().calculate(s))
