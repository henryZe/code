# 模拟
class Solution:
    def minimumNumbers(self, num: int, k: int) -> int:
        cur_sum = 0
        times = 0
        s = set()

        while cur_sum < num:
            cur_sum += k
            times += 1

            if cur_sum % 10 == num % 10:
                break

            r = cur_sum % 10
            if r in s:
                times = -1
                break
            s.add(r)

        if cur_sum > num:
            return -1

        return times

num, k = 58, 9
# num, k = 37, 2
# num, k = 0, 7
print(Solution().minimumNumbers(num, k))
