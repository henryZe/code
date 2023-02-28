#include <stdbool.h>
#include <stdlib.h>

struct node {
    int x, y;
    int value;
    int parent;
    bool visited;
};

int pos2idx(int x, int y, int colSize)
{
    return x * colSize + y;
}

struct node *array;

int compare(const void *a, const void *b)
{
    int idx1 = *(int *)a, idx2 = *(int *)b;
    return array[idx2].value - array[idx1].value;
}

struct node dir_array[] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int find_set(struct node *array, int idx)
{
    if (array[idx].parent != idx)
        array[idx].parent = find_set(array, array[idx].parent);

    return array[idx].parent;
}

void union_set(struct node *array, int idx1, int idx2)
{
    // parent[root1] = root2
    array[find_set(array, idx1)].parent = find_set(array, array[idx2].parent);
}

int maximumMinimumPath(int** grid, int gridSize, int* gridColSize)
{
    int i, j;
    int count = gridSize * gridColSize[0];
    int *sort_idx = malloc(sizeof(int) * count);
    array = malloc(sizeof(struct node) * count);

    for (i = 0; i < count; i++)
        sort_idx[i] = i;

    // initialize the array of nodes
    for (i = 0; i < gridSize; i++) {
        for (j = 0 ; j < gridColSize[i]; j++) {
            struct node *n = array + pos2idx(i, j, gridColSize[0]);

            n->x = i;
            n->y = j;

            n->value = grid[i][j];
            n->parent = pos2idx(i, j, gridColSize[0]);
            n->visited = false;
        }
    }

    // 1. sort the node by value
    qsort(sort_idx, count, sizeof(int), compare);

    // 2. pick the max value edge, and union
    for (i = 0; i < count; i++) {
        int idx1 = sort_idx[i];

        array[idx1].visited = true;
        for (j = 0; j < 4; j++) {
            int new_x = array[idx1].x + dir_array[j].x;
            int new_y = array[idx1].y + dir_array[j].y;

            if (new_x >= 0 && new_x < gridSize &&
                new_y >= 0 && new_y < gridColSize[0]) {
                int idx2 = pos2idx(new_x, new_y, gridColSize[0]);

                if (array[idx2].visited) {
                    // printf("union: idx1 = %d, idx2 = %d\n", idx1, idx2);

                    union_set(array, idx1, idx2);
                }
            }
        }

        // 3. check the head & end already union or not
        int head_root = find_set(array, pos2idx(0, 0, gridColSize[0]));
        int end_root = find_set(array, pos2idx(gridSize - 1, gridColSize[0] - 1, gridColSize[0]));

        // printf("check: head_root = %d, end_root = %d\n",
        //         head_root, end_root);

        // 4. if union, then the current edge value is the answer
        if (head_root == end_root)
            return array[idx1].value;
    }

    return 0;
}
