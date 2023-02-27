#define M 301

int rank[M][M] = {};
int parent[M][M] = {};

int find_set(int gridSize, int *gridColSize, int i, int j)
{
    if (parent[i][j] != (i * gridColSize[0] + j))
        parent[i][j] = find_set(gridSize, gridColSize,
                                parent[i][j] / gridColSize[0],
                                parent[i][j] % gridColSize[0]);
    return parent[i][j];
}

bool union_set(int gridSize, int *gridColSize, int i, int j, int x, int y)
{
    int p_root = find_set(gridSize, gridColSize, i, j);
    int q_root = find_set(gridSize, gridColSize, x, y);

    if (p_root == q_root)
        // already union
        return false;

    if (rank[i][j] == rank[x][y])
        rank[i][j]++;

    if (rank[i][j] > rank[x][y])
        parent[q_root / gridColSize[0]][q_root % gridColSize[0]] = p_root;
    else
        parent[p_root / gridColSize[0]][p_root % gridColSize[0]] = q_root;

    // union
    return true;
}

int numIslands(char** grid, int gridSize, int* gridColSize)
{
    int i, j;
    int res = 0;
    int count = 0;

    for (i = 0; i < gridSize; i++) {
        for (j = 0; j < gridColSize[i]; j++) {
            parent[i][j] = i * gridColSize[0] + j;
        }
    }

    for (i = 0; i < gridSize; i++) {
        for (j = 0; j < gridColSize[i]; j++) {
            if (grid[i][j] == '0')
                continue;

            count++;

            if ((i + 1) < gridSize && grid[i + 1][j] == '1') {
                if (union_set(gridSize, gridColSize, i, j, i + 1, j))
                    count--;
            }

            if ((j + 1) < gridColSize[0] && grid[i][j + 1] == '1') {
                if (union_set(gridSize, gridColSize, i, j, i, j + 1))
                    count--;
            }
        }
    }

    return count;
}
