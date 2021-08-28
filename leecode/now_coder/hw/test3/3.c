#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void print_matrix(int a[9][9])
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int get_matrix(int a[9][9])
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            char str[8];
            scanf("%s ", str);
            a[i][j] = atoi(str);
        }
    }

    return 0;
}

int check(int a[9][9], int r, int c, int num)
{
    for (int i = 0; i < 9; i++) {
        if (a[r][i] == num || a[i][c] == num)
            return false;

        if (a[r / 3 * 3 + i / 3][c / 3 * 3 + i % 3] == num)
            return false;
    }

    return true;
}

int backtrace(int a[9][9], int r, int c)
{
    int num;

    if (r == 9)
        return true;

    if (c == 9)
        return backtrace(a, r + 1, 0);

    if (a[r][c])
        return backtrace(a, r, c + 1);

    for (num = 1; num < 10; num++) {
        if (check(a, r, c, num) == false)
            continue;

        a[r][c] = num;
        if (backtrace(a, r, c + 1) == true)
            break;
        a[r][c] = 0;
    }

    if (num == 10)
        return false;

    return true;
}

int fill_matrix(int a[9][9])
{
    return backtrace(a, 0, 0);
}

int main(void)
{
    int a[9][9];

    get_matrix(a);
    // print_matrix(a);
    // printf("\n\n");

    int ret = fill_matrix(a);
    if (ret == true)
        print_matrix(a);
    else
        printf("Error\n");

    return 0;
}
