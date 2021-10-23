#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dfs(char** grid, int gridRowLen, int* gridColLen, int row, int col)
{
    if (row < 0)
        return;
    if (row >= gridRowLen)
        return;
    if (col < 0)
        return;
    if (col >= gridColLen[row])
        return;

    if (grid[row][col] == '0')
        return;

    grid[row][col] = '0';
    dfs(grid, gridRowLen, gridColLen, row + 1, col);
    dfs(grid, gridRowLen, gridColLen, row - 1, col);
    dfs(grid, gridRowLen, gridColLen, row, col + 1);
    dfs(grid, gridRowLen, gridColLen, row, col - 1);
}

int solve(char** grid, int gridRowLen, int* gridColLen)
{
    int island = 0;
    for (int i = 0; i < gridRowLen; i++) {
        for (int j = 0; j < gridColLen[i]; j++) {
            if (grid[i][j] == '1') {
                island++;
                dfs(grid, gridRowLen, gridColLen, i, j);
            }
        }
    }

    return island;
}

int main(void)
{
    char row0[] = {
        '1','1','0','1','0'
    };
    char row1[] = {
        '0','1','1','1','1'
    };
    char row2[] = {
        '0','0','0','1','1'
    };
    char row3[] = {
        '0','0','1','1','0'
    };
    char row4[] = {
        '0','0','0','0','1'
    };
    char *matrix[] = {
        row0,
        row1,
        row2,
        row3,
        row4,
    };
    int gridColLen[] = {
        5,5,5,5,5
    };
    printf("%d\n", solve(matrix, 5, gridColLen));

    // char row0[] = {
    //     '1'
    // };
    // char *matrix[] = {
    //     row0,
    // };
    // int gridColLen[] = {
    //     1
    // };
    // printf("%d\n", solve(matrix, 1, gridColLen));
    return 0;
}