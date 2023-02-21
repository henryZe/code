/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int find_set(int *parent, int idx)
{
    if (parent[idx] != idx)
        // update one's parent
        parent[idx] = find_set(parent, parent[idx]);
    return parent[idx];
}

void union_set(int *parent, int idx1, int idx2)
{
    parent[find_set(parent, idx1)] = find_set(parent, idx2);
}

int* findRedundantConnection(int** edges, int edgesSize, int* edgesColSize, int* returnSize)
{
    int i;
    int *res = malloc(sizeof(int) * 2);
    int *parent = malloc(sizeof(int) * (edgesSize + 1));

    for (i = 0; i <= edgesSize; i++) {
        parent[i] = i;
    }

    for (i = 0; i < edgesSize; i++) {
        int idx1 = edges[i][0], idx2 = edges[i][1];

        if (find_set(parent, idx1) == find_set(parent, idx2)) {
            res[0] = idx1;
            res[1] = idx2;
            continue;
        }

        union_set(parent, idx1, idx2);
    }

    *returnSize = 2;
    return res;
}
