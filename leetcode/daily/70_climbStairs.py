
class Solution:
    def climbStairs(self, n: int) -> int:
        level = [1] * (n + 1)
        level[0] = 1
        level[1] = 1

        for i in range(2, n + 1):
            level[i] = level[i - 1] + level[i - 2]

        return level[-1]

print(Solution().climbStairs(2))
print(Solution().climbStairs(3))