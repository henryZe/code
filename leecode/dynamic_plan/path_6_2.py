import numpy as np
from scipy.special import comb

class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        if 0:
            def search(num:int, i: int, j: int) -> int:
                if i >= m or j >= n:
                    return num

                if i == m - 1 and j == n - 1:
                    num += 1
                    return num

                num = search(num, i + 1, j)
                num = search(num, i, j + 1)

                return num

            return search(0, 0, 0)

        if 1:
            f = np.ones((m, n), dtype=int)
            for i in range(1, m):
                for j in range(1, n):
                    f[i][j] = f[i-1][j] + f[i][j-1]

            return f[m-1][n-1]
        
        if 0:
            return comb(m + n - 2, m - 1)

obj = Solution()
print(obj.uniquePaths(20, 12))
