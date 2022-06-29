#include <stdbool.h>
#include <stdio.h>
#include <string.h>

struct pos {
    int x;
    int y;
};

#define MAX_LINE 100

int rule_1[MAX_LINE][MAX_LINE] = {0};
int rule_2[MAX_LINE][MAX_LINE] = {0};

struct pos around[4] = {
    [0] = {
        .x = -1,
        .y = 0,
    },
    [1] = {
        .x = 0,
        .y = -1,
    },
    [2] = {
        .x = 1,
        .y = 0,
    },
    [3] = {
        .x = 0,
        .y = 1,
    },
};

int cal_rule1(int **growth, int growthSize, int *growthColSize)
{
    for (int i = 0; i < MAX_LINE; i++) {
        memset(rule_1[i], 0, sizeof(int) * MAX_LINE);
    }

    for (int x = 0; x < growthSize; x++) {
        for (int y = 0; y < growthColSize[x]; y++) {
            int sum = 0;
            for (int pos = 0; pos < 4; pos++) {
                int new_x = x + around[pos].x;
                int new_y = y + around[pos].y;

                if ((0 <= new_x && new_x < growthSize) && (0 <= new_y && new_y < growthColSize[x])) {
                    sum += growth[new_x][new_y];
                }
            }
            if (sum >= 21) {
                rule_1[x][y] = -5;
            }
        }
    }

    return 0;
}

int cal_rule2(int **growth, int growthSize, int *growthColSize)
{
    for (int i = 0; i < MAX_LINE; i++) {
        memset(rule_2[i], 0, sizeof(int) * MAX_LINE);
    }

    for (int x = 0; x < growthSize; x++) {
        for (int y = 0; y < growthColSize[x]; y++) {
            if (growth[x][y] <= 0)
                continue;

            for (int pos = 0; pos < 4; pos++) {
                int new_x = x + around[pos].x;
                int new_y = y + around[pos].y; 
            
                if ((0 <= new_x && new_x < growthSize) && (0 <= new_y && new_y < growthColSize[x])) {
                    rule_2[new_x][new_y] += 1;
                }
            }
        }
    }

    return 0;
}

int cal_cur(int **growth, int growthSize, int *growthColSize)
{
    for (int x = 0; x < growthSize; x++) {
        for (int y = 0; y < growthColSize[x]; y++) {
            growth[x][y] += rule_1[x][y] + rule_2[x][y];
        }
    }
    return 0;
}

int cal_sum(int **growth, int growthSize, int *growthColSize)
{
    int sum = 0;
    for (int x = 0; x < growthSize; x++) {
        for (int y = 0; y < growthColSize[x]; y++) {
            sum += growth[x][y];
        }
    }
    return sum;
}

int GetPlantLushSums(int **growth, int growthSize, int *growthColSize,
                    int *interfere, int interfereSize, int time)
{
    for (int i = 1; i <= time; i++) {
        cal_rule1(growth, growthSize, growthColSize);
        cal_rule2(growth, growthSize, growthColSize);
        if (i == interfere[0]) {
            growth[interfere[1]][interfere[2]] += interfere[3];
        }
        cal_cur(growth, growthSize, growthColSize);
    }

    int ret = cal_sum(growth, growthSize, growthColSize);
    printf("sum = %d\n", ret);
    return ret;
}

bool TEST1(void)
{
    int row1[] = {4,8,4,10};
    int row2[] = {0,3,4,5};
    int row3[] = {2,10,9,7};
    int *growth[] = {row1, row2, row3};
    int growthColSize[] = {sizeof(row1) / sizeof(int), sizeof(row2) / sizeof(int), sizeof(row3) / sizeof(int)};

    int interfere[] = {1,2,3,5};
    int interfereSize = 4;

    int time = 2;

    int ret = GetPlantLushSums(growth, sizeof(growth) / sizeof(int*),
                                growthColSize, interfere, interfereSize, time);
    return (ret == 91);
}

bool TEST2(void)
{
    int row1[] = {0,3};
    int row2[] = {2,0};
    int *growth[] = {row1, row2};
    int growthColSize[] = {sizeof(row1) / sizeof(int), sizeof(row2) / sizeof(int)};

    int interfere[] = {1,0,0,-10};
    int interfereSize = 4;

    int time = 1;

    int ret = GetPlantLushSums(growth, sizeof(growth) / sizeof(int*),
                                growthColSize, interfere, interfereSize, time);
    return (ret == -1);
}

int main(void)
{
    bool ret = TEST1();
    if (!ret)
        printf("TEST1 fail\n");

    ret = TEST2();
    if (!ret)
        printf("TEST1 fail\n");

    return 0;
}