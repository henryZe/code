class Solution:
    def sumOfNumberAndReverse(self, num: int) -> bool:
        def rev(num):
            num_rev = 0
            while num:
                num_rev = num_rev * 10 + num % 10
                num //= 10
            return num_rev

        if num == 0:
            return True

        for i in range(num):
            if i + rev(i) == num:
                return True

        return False

num = 443
num = 63
num = 181
print(Solution().sumOfNumberAndReverse(num))
