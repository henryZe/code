/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2021. All rights reserved.
 * Description: 上机编程认证
 * Note: 缺省代码仅供参考，可自行决定使用、修改或删除
 */
#include <stdio.h>
#include <stdlib.h>
#include "securec.h"

#define MAX_ROW_SIZE 100
#define MAX_COL_SIZE 100

// 待实现函数，在此函数中填入答题代码
static int calcTheNthWeight(const int **weightMatrix, int rows, int cols, int num)
{
    int i, j;
    int num = 1;

    for (i = 0; i < rows; i++) {
        num *= cols;
    }

    int *sort_array = malloc(sizeof(int) * num);

    int tmp;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < col)

        choose_one()
    }
    return 0;
}

int main(void)
{
    int rowCount, colCount;
    if (scanf("%d %d", &rowCount, &colCount) != 2) { return -1; }

    static int buf[MAX_ROW_SIZE][MAX_COL_SIZE];
    int *weightMatrix[MAX_ROW_SIZE];
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            if (scanf("%d", &buf[i][j]) != 1) { return -1; }
        }
        weightMatrix[i] = buf[i];
    }

    int num;
    if (scanf("%d", &num) != 1) { return -1; }

    int output = calcTheNthWeight(weightMatrix, rowCount, colCount, num);
    printf("%d", output);

    return 0;
}
