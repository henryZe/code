// dfs
void dfs(int** isConnected, int *visit, int cur, int *isConnectedColSize)
{
    int i;

    visit[cur] = 1;

    for (i = 0; i < isConnectedColSize[cur]; i++) {
        if (isConnected[cur][i] != 0 && visit[i] == 0)
            dfs(isConnected, visit, i, isConnectedColSize);
    }
}

int findCircleNum(int** isConnected, int isConnectedSize, int* isConnectedColSize)
{
    int res = 0;
    int i;
    int *visit = malloc(isConnectedSize * sizeof(int));
    for (i = 0; i < isConnectedSize; i++) {
        visit[i] = 0;
    }

    for (i = 0; i < isConnectedSize; i++) {
        if (!visit[i]) {
            dfs(isConnected, visit, i, isConnectedColSize);
            res++;
        }
    }

    return res;
}
