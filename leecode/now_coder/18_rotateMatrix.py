# -*- coding:utf-8 -*-

class Solution:
    def rotateMatrix(self, mat, n):
        new_m = []
        for r in range(n):
            row = [0] * n
            new_m.append(row)

        for r in range(n):
            for c in range(n):
                new_m[c][n - 1 - r] = mat[r][c]

        return new_m