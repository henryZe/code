class Solution:
    def smallestNumber(self, pattern: str) -> str:
        n = len(pattern) + 1
        candidate = set(range(1, n + 1))
        num = ['0'] * n

        for i, c in enumerate(pattern):
            if c == 'I':
                num[i] = min(candidate) + '0'
                candidate.remove(num[i])

        for i, c in enumerate(pattern):
            if c == 'D':
                num[i] = max(candidate) + '0'
                candidate.remove(num[i])

        return "".join(num)

pattern = "DDD"
print(Solution().smallestNumber(pattern))
