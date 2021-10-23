class Solution:
    def tribonacci(self, n: int) -> int:
        array = [0, 1, 1]

        if n < 3:
            return array[n]

        ret = 0
        for i in range(3, n + 1):
            ret = array[0] + array[1] + array[2]
            array[0] = array[1]
            array[1] = array[2]
            array[2] = ret

        return ret

print(Solution().tribonacci(25))