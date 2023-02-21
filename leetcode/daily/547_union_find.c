
int find_set(int *parent, int idx)
{
    if (parent[idx] != idx)
        // shorten the distance
        parent[idx] = find_set(parent, parent[idx]);
    return parent[idx];
}

void union_set(int *parent, int idx1, int idx2)
{
    parent[find_set(parent, idx1)] = find_set(parent, idx2);
}

int findCircleNum(int** isConnected, int isConnectedSize, int* isConnectedColSize)
{
    int i, j, res = 0;
    int *parent = malloc(isConnectedSize * sizeof(int));

    for (i = 0; i < isConnectedSize; i++)
        parent[i] = i;

    for (i = 0; i < isConnectedSize; i++) {
        for (j = i + 1; j < isConnectedColSize[i]; j++) {
            if (isConnected[i][j] == 1) {
                union_set(parent, i, j);
            }
        }
    }

    for (i = 0; i < isConnectedSize; i++) {
        if (parent[i] == i)
            res++;
    }

    return res;
}
