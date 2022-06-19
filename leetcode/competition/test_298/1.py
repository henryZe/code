# 模拟
class Solution:
    def greatestLetter(self, s: str) -> str:
        set_upper_char = set()
        set_lower_char = set()
        for c in s:
            if c.islower():
                set_lower_char.add(c)
            else:
                set_upper_char.add(c)

        for c in range(ord('Z'), ord('A') - 1, -1):
            if chr(c) in set_upper_char:
                if chr(c - ord('A') + ord('a')) in set_lower_char:
                    return chr(c)

        return ''

# s = "lEeTcOdE"
# s = "arRAzFif"
s = "AbCdEfGhIjK"
print(Solution().greatestLetter(s))
