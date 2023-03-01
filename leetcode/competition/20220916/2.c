#include <math.h>
#include <stdlib.h>

/*
 * planks是长度为planksSize的数组，其元素为指针，
 * planksColSize[i] 表示 planks[i] 所指向内容的长度，
 * planksColSize的长度也为planksSize。
 */
int calc(int **planks, int max_col, int i, int j, int **m)
{
        int dp[max_col];
        int step = 0;
        if (planks[i][j] == 1) {
                while (j >= 0 && m[i][j] != 0) {
                        step++;
                        m[i][j - 1] = fmin(step, m[i][j - 1]);
                        if (m[i][j - 1] == step) {
                                break;
                        }

                }
                return 0;
        }


        if (j == 0)
                return 2000;

        if (m[i][j - 1] == 2000)
                return 2000;

        return m[i][j - 1] + 1;
}

int GetMinMovesNum(int **planks, int planksSize,
                        int *planksColSize)
{
        int i = 0;
        int **m = malloc(planksSize * sizeof(int *));
        for (i = 0; i < planksSize; i++) {
                m[i] = malloc(sizeof(int) * planksColSize[i]);
        }

        int j;
        for (i = 0; i < planksSize; i++) {
                for (j = 0; j < planksColSize[i]; j++) {
                        m[i][j] = calc(planks, planksColSize[0], i, j, m);
                }
        }

        int *sum = malloc(planksColSize[0] * sizeof(int));
        for (i = 0; i < planksColSize[0]; i++)
                sum[i] = 0;

        for (j = 0; j < planksColSize[0]; j++) {
                for (i = 0; i < planksSize; i++) {
                        sum[j] += m[i][j];
                }
        }

        int res = sum[0];
        for (i = 0; i < planksColSize[0]; i++)
                res = fmin(res, sum[i]);
        return res;
}
