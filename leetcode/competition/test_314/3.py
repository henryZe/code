from typing import Counter

def idx_chr(idx):
    return chr(ord('a') + idx)

class Solution:
    def robotWithString(self, s: str) -> str:
        n = len(s)
        # O(n)
        c = Counter(s)
        stack = []
        res = []
        min_c = 0

        # O(n)
        for i in s:
            c[i] -= 1
            while min_c < 25 and c[idx_chr(min_c)] == 0:
                min_c += 1
            stack.append(i)

            while stack and stack[-1] <= idx_chr(min_c):
                res.append(stack.pop())

        return "".join(res)


# s = "zza"
# s = "bac"
s = "bdda"
print(Solution().robotWithString(s))
