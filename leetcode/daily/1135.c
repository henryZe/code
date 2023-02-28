#include <stdlib.h>

int **edges;

int compare(const void *a, const void *b)
{
    int idx1 = *(int *)a, idx2 = *(int *)b;
    return edges[idx1][2] - edges[idx2][2];
}

int find_set(int *parent, int idx)
{
    if (parent[idx] != idx)
        parent[idx] = find_set(parent, parent[idx]);
    return parent[idx];
}

void union_set(int *parent, int idx1, int idx2)
{
    parent[find_set(parent, idx1)] = find_set(parent, idx2);
}

int minimumCost(int n, int** connections, int connectionsSize, int* connectionsColSize)
{
    int i;
    int count = 0, res = 0;
    int *idx = malloc(connectionsSize * sizeof(int));
    int *parent = malloc((n + 1) * sizeof(int));

    for (i = 0; i < connectionsSize; i++)
        idx[i] = i;

    for (i = 1; i <= n; i++)
        parent[i] = i;

    // 1. sort edges by value, then choose the min edge
    edges = connections;
    qsort(idx, connectionsSize, sizeof(int), compare);

    for (i = 0; i < connectionsSize; i++) {
        int *edge = connections[idx[i]];

        // 2. if no loop (check by union-find) internal, then include this edge
        if (find_set(parent, edge[0]) == find_set(parent, edge[1]))
            continue;

        union_set(parent, edge[0], edge[1]);
        res += edge[2];
        count++;

        // 3. if number of edge is n - 1, then all connected
        if (count == (n - 1))
            break;
    }

    if (count != (n - 1))
        return -1;

    return res;
}
