from typing import List

class Solution:
    def reverseString(self, s: List[str]) -> None:
        a = 0
        b = len(s) - 1
        while a < b:
            temp = s[b]
            s[b] = s[a]
            s[a] = temp
            a += 1
            b -= 1
        return

s = ["h","e","l","l","o"]
Solution().reverseString(s)
print(s)
