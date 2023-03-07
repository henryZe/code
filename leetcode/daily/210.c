#include <stdbool.h>

bool dfs(int *res, int *res_len, int **edges, int edges_num[], int visited[], int v)
{
    int i;

    // assert(visited[v] != 1);
    if (visited[v] == 2)
        return true;

    // set v as searching
    visited[v] = 1;

    for (i = 0; i < edges_num[v]; i++) {
        int w = edges[v][i];

        if (visited[w] == 0) {
            if (!dfs(res, res_len, edges, edges_num, visited, w)) {
                return false;
            }

        } else if (visited[w] == 1) {
            // loop exist
            return false;
        }
    }

    res[*res_len] = v;
    (*res_len)++;

    // set v as finish
    visited[v] = 2;
    return true;
}

int* findOrder(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize, int* returnSize)
{
    int i;
    int *edges[numCourses];
    int edges_num[numCourses];

    for (i = 0; i < numCourses; i++) {
        edges[i] = malloc(sizeof(int) * numCourses);
        edges_num[i] = 0;
    }

    for (i = 0; i < prerequisitesSize; i++) {
        int v = prerequisites[i][0];
        int w = prerequisites[i][1];

        // printf("v %d %d: w %d\n", v, edges_num[v], w);
        edges[v][edges_num[v]] = w;
        edges_num[v]++;
    }

    bool ret = true;
    int *res = malloc(sizeof(int) * numCourses);
    int res_len = 0;
    // 0: not visit yet
    // 1: searching
    // 2: visited
    int visited[numCourses];

    for (i = 0; i < numCourses; i++) {
        visited[i] = 0;
    }

    for (i = 0; i < numCourses; i++) {
        ret = dfs(res, &res_len, edges, edges_num, visited, i);
        if (!ret)
            break;
    }

    if (!ret) {
        *returnSize = 0;
        return NULL;
    }

    *returnSize = numCourses;
    return res;
}
