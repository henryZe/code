class Solution:
    def clumsy(self, N: int) -> int:
        option = ("*", "/", "+", "-")
        n = len(option)
        stack = [N]
        N -= 1

        index = 0
        while N:
            if index % n == 0:
                stack.append(stack.pop() * N)
            elif index % n == 1:
                tmp = stack.pop()
                if tmp < 0:
                    stack.append(-(-tmp // N))
                else:
                    stack.append(tmp // N)
            elif index % n == 2:
                stack.append(N)
            else:
                stack.append(-N)

            N -= 1
            index += 1

        return sum(stack[::])

# N = 4
N = 10
print(Solution().clumsy(N))