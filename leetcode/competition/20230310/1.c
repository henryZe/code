
/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2023. All rights reserved.
 * Description: 上机编程认证
 * Note: 缺省代码仅供参考，可自行决定使用、修改或删除
 */
#include <stdio.h>
#include "securec.h"

// 用例规格不超过下面定义
#define MAX_STR_LEN 8
#define MAXN 20
#define BUF_LEN 32
#define MAXLINE 101

#define debug(...)

typedef struct {
    int row;
    int col;
    char str[MAX_STR_LEN];      // 若为空字符串，表示输入为空
} SheetInfo;

void print_intro(int col)
{
    int i;

    printf("+");
    for (i = 0; i < col; i++) {
        printf("---+");
    }
    printf("\n");
}
void print_context(char table[MAXLINE][MAXLINE], int line, int col)
{
    int i;
    printf("|");

    for (i = 1; i <= col; i++) {
        debug("%d", table[line][i]);
        printf(" %c |", table[line][i]);
    }

    printf("\n");
}

// 待实现函数，在此函数中填入答题代码。输出内容由实现者自行打印。
static void TransformTable(const SheetInfo *sheetInfo, int num)
{
    int i;
    int j;
    char table[MAXLINE][MAXLINE];

    for (i = 0; i < MAXLINE; i++) {
        for (j = 0; j < MAXLINE; j++) {
            table[i][j] = ' ';
        }
    }

    int line;
    int col;
    int max_line = 1;
    int max_col = 1;

    for (i = 0; i < num; i++) {
        line = sheetInfo[i].row;
        if (line > max_line) {
            max_line = line;
        }

        col = sheetInfo[i].col;
        if (col > max_col) {
            max_col = col;
        }

        if (sheetInfo[i].str[0] != 0) {
            table[line][col] = sheetInfo[i].str[0];
        }
    }

    print_intro(max_col);

    for (i = 1; i <= max_line; i++) {
        print_context(table, i, max_col);
    }

    print_intro(max_col);
}

// 以下为考题输入输出框架，此部分代码不建议改动
static int ParseSheetInfo(const char inputStr[][BUF_LEN], int num, SheetInfo *sheetInfo)
{
    for (int i = 0; i < num; i++) {
        int row;
        int col;
        size_t len = strlen(inputStr[i]);
        if (len < 1) { return 0; }
        char tmpStr[MAX_STR_LEN] = { 0 };
        if (inputStr[i][len - 1] >= 'A' && inputStr[i][len - 1] <= 'Z') {
            if (sscanf_s(inputStr[i], "line%d col%d %s", &row, &col, tmpStr, sizeof(tmpStr)) != 3) { return 0; }
        } else {
            if (sscanf_s(inputStr[i], "line%d col%d", &row, &col) != 2) { return 0; }
        }

        sheetInfo[i].col = col;
        sheetInfo[i].row = row;
        if (strcpy_s(sheetInfo[i].str, MAX_STR_LEN, tmpStr) != EOK) { return 0; }
    }
    return num;
}

int main(void)
{
    int num;
    if (scanf_s("%d", &num) != 1) { return -1; }

    (void)getchar();

    static char inputStr[MAXN][BUF_LEN];
    for (int i = 0; i < num; i++) {
        if (gets_s(inputStr[i], sizeof(inputStr[i])) == NULL) { return -1; }
    }

    SheetInfo sheetInfo[MAXN] = { 0 };
    if (ParseSheetInfo(inputStr, num, sheetInfo) <= 0) { return -1; }

    TransformTable(sheetInfo, num);

    return 0;
}
