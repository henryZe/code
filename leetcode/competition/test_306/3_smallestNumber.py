from string import digits

class Solution:
    def smallestNumber(self, pattern: str) -> str:
        n = len(pattern)
        num = list(digits[1 : n + 2])

        i = 0
        while i < n:
            if pattern[i] == 'I':
                i += 1
                continue
            # pattern[i] = 'D'
            start = i
            while i < n and pattern[i] == 'D':
                i += 1
            num[start : i + 1] = num[start : i + 1][::-1]

        return "".join(num)


pattern = "IIIDIDDD"
# pattern = "DDD"
print(Solution().smallestNumber(pattern))
