
void dfs(char **grid, int gridSize, int *gridColSize, int i, int j)
{
    grid[i][j] = '0';

    if ((i + 1) < gridSize) {
        if (grid[i + 1][j] == '1')
            dfs(grid, gridSize, gridColSize, i + 1, j);
    }

    if ((i - 1) >= 0) {
        if (grid[i - 1][j] == '1')
            dfs(grid, gridSize, gridColSize, i - 1, j);
    }

    if ((j + 1) < gridColSize[i]) {
        if (grid[i][j + 1] == '1')
            dfs(grid, gridSize, gridColSize, i, j + 1);
    }

    if ((j - 1) >= 0) {
        if (grid[i][j - 1] == '1')
            dfs(grid, gridSize, gridColSize, i, j - 1);
    }
}

int numIslands(char** grid, int gridSize, int* gridColSize)
{
    int i, j;
    int res = 0;

    for (i = 0; i < gridSize; i++) {
        for (j = 0; j < gridColSize[i]; j++) {
            if (grid[i][j] == '1') {
                dfs(grid, gridSize, gridColSize, i, j);
                res++;
            }
        }
    }

    return res;
}
