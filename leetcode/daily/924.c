int find_set(int *parent, int i)
{
    if (parent[i] != i)
        parent[i] = find_set(parent, parent[i]);
    return parent[i];
}

void union_set(int *parent, int *rank, int i, int j)
{
    int p = find_set(parent, i);
    int q = find_set(parent, j);

    if (p != q) {
        if (rank[p] == rank[q])
            rank[p]++;

        if (rank[p] > rank[q]) {
            parent[q] = p;
        } else {
            parent[p] = q;
        }
    }
}

int find_min(int *initial, int initialSize)
{
    int i;
    int res = initial[0];

    for (i = 1; i < initialSize; i++) {
        if (initial[i] < res)
            res = initial[i];
    }

    return res;
}

int minMalwareSpread(int** graph, int graphSize, int* graphColSize,
                     int* initial, int initialSize)
{
    int i, j;

    // 1. complete union-find-set
    int *parent = malloc(sizeof(int) * graphSize);
    int *rank = malloc(sizeof(int) * graphSize);
    for (i = 0; i < graphSize; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (i = 0; i < graphSize; i++) {
        for (j = i + 1; j < graphSize; j++) {
            if (graph[i][j] == 1) {
                union_set(parent, rank, i, j);
            }
        }
    }

    // 2. find the number of each set
    int *count = malloc(sizeof(int) * graphSize);
    memset(count, 0, sizeof(int) * graphSize);

    for (i = 0; i < graphSize; i++) {
        count[parent[i]]++;
    }

    // 3. sort the set by total number,
    // find the one only include one infect
    int *infect = malloc(sizeof(int) * graphSize);
    memset(infect, 0, sizeof(int) * graphSize);

    for (i = 0; i < initialSize; i++) {
        infect[parent[initial[i]]]++;
    }

    // 4. if multiple answers exist,
    // return the minimum initial
    int res = -1;

    for (i = 0; i < initialSize; i++) {
        int set_index = parent[initial[i]];

        // printf("initial %d set_index %d count %d infect %d\n",
        //         initial[i], set_index, count[set_index],
        //         infect[set_index]);

        if (infect[set_index] == 1) {
            if (res == -1) {
                res = initial[i];
                continue;
            }

            if (count[set_index] > count[parent[res]]) {
                res = initial[i];
                continue;
            }

            if (count[set_index] == count[parent[res]]) {
                if (initial[i] < res) {
                    res = initial[i];
                }
            }
        }
    }

    // 5. if no one meets, then choose the minimum index
    if (res == -1) {
        // printf("choose min\n");
        return find_min(initial, initialSize);
    }

    return res;
}
