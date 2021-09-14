#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int minPathSum(int** matrix, int matrixRowLen, int* matrixColLen)
{
    int *dp[matrixRowLen];
    for (int i = 0; i < matrixRowLen; i++) {
        dp[i] = (int *)malloc(matrixColLen[i] * sizeof(int));
    }

    dp[0][0] = matrix[0][0];
    for (int r = 1; r < matrixRowLen; r++) {
        dp[r][0] = matrix[r][0] + dp[r - 1][0];
    }
    for (int c = 1; c < matrixColLen[0]; c++) {
        dp[0][c] = matrix[0][c] + dp[0][c - 1];
    }

    for (int r = 1; r < matrixRowLen; r++) {
        for (int c = 1; c < matrixColLen[r]; c++) {
            dp[r][c] = fmin(dp[r - 1][c], dp[r][c - 1]) + matrix[r][c];
        }
    }

    return dp[matrixRowLen - 1][matrixColLen[matrixRowLen - 1] - 1];
}

int main(void)
{
    int row0[] = {1,3,5,9};
    int row1[] = {8,1,3,4};
    int row2[] = {5,0,6,1};
    int row3[] = {8,8,4,0};
    int *matrix[] = {
        row0,
        row1,
        row2,
        row3,
    };
    int matrixRowLen = 4;
    int matrixColLen[] = {4,4,4,4};

    printf("%d\n", minPathSum(matrix, matrixRowLen, matrixColLen));
    return 0;
}
