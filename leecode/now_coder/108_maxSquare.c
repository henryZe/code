#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SQ_VALID '1'

int test_square(char** matrix, int r, int c, int len)
{
    for (int i = 1; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (matrix[r + i][c + j] != SQ_VALID) {
                return 0;
            }
        }
    }

    return 1;
}

int judge_length(char** matrix, int matrixRowLen, int* matrixColLen, int r, int c)
{
    int ci = 0;

    while ((c + ci < matrixColLen[r]) && matrix[r][c + ci] == SQ_VALID) {
        ci++;
    }

    int ri = 0;
    while ((r + ri < matrixRowLen) && matrix[r + ri][c] == SQ_VALID) {
        ri++;
    }

    int i = ci < ri ? ci : ri;

    int ret;
    while (i) {
        ret = test_square(matrix, r, c, i);
        if (ret)
            break;
        i--;
    }

    return i;
}

int solve(char** matrix, int matrixRowLen, int* matrixColLen)
{
    int max_len = 0;

    for (int r = 0; r < matrixRowLen; r++) {
        for (int c = 0; c < matrixColLen[r]; c++) {
            int len = judge_length(matrix, matrixRowLen, matrixColLen, r, c);
            max_len = len > max_len ? len : max_len;
        }
    }

    return max_len * max_len;
}

int main(void)
{
    char matrix_r0[] = { '1','0','1','0','0' };
    char matrix_r1[] = { '1','0','1','1','1' };
    char matrix_r2[] = { '1','1','1','1','1' };
    char matrix_r3[] = { '1','0','0','1','0' };
    char *matrix[] = {
        matrix_r0,
        matrix_r1,
        matrix_r2,
        matrix_r3
    };
    int matrixRowLen = 4;
    int matrixColLen[] = {
        sizeof(matrix_r0),
        sizeof(matrix_r1),
        sizeof(matrix_r2),
        sizeof(matrix_r3),
    };

    int ret = solve(matrix, matrixRowLen, matrixColLen);
    printf("%d\n", ret);

    return 0;
}
