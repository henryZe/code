from typing import List

class Solution:
    def convert(self, s: str, numRows: int) -> str:
        if numRows == 1:
            return s

        matrix = []
        for _ in range(numRows):
            matrix.append([])

        r = 0
        c = 0
        for i in s:
            if c % (numRows - 1) == 0:
                matrix[r].append(i)
                if r + 1 < numRows:
                    r += 1
                    continue
            else:
                matrix[r].append(i)

            r -= 1
            c += 1

        ret = ""
        for l in matrix:
            ret += "".join(l)
        return ret

# s = "PAYPALISHIRING"
# numRows = 3
# s = "PAYPALISHIRING"
# numRows = 4
s = "A"
numRows = 1
print(Solution().convert(s, numRows))
