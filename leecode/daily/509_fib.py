class Solution:
    def fib(self, n: int) -> int:
        last = 1
        nextLast = 0
        fib_num = 0

        if (n == 0):
            return nextLast
        if (n == 1):
            return last

        for i in range(2, n + 1):
            fib_num = last + nextLast
            nextLast = last
            last = fib_num
        return fib_num

print(Solution().fib(2))