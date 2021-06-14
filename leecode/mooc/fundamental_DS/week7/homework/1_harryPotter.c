#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

struct graph {
    int Nv;
    int **vmatrix;
};

struct graph *create_graph(int v_num)
{
    struct graph *G = malloc(sizeof(struct graph));

    G->Nv = v_num;
    G->vmatrix = malloc(sizeof(int *) * (v_num + 1));
    for (int i = 1; i <= v_num; i++) {
        G->vmatrix[i] = malloc(sizeof(int) * (v_num + 1));
        for (int j = 1; j <= v_num; j++) {
            if (i == j)
                // circle self
                G->vmatrix[i][j] = 0;
            else
                G->vmatrix[i][j] = INT_MAX;
        }
    }

    return G;
}

int insert_edge(struct graph *G, int e_num)
{
    int v, w, weight;
    for (int i = 0; i < e_num; i++) {
        scanf("%d %d %d\n", &v, &w, &weight);
        G->vmatrix[v][w] = weight;
        G->vmatrix[w][v] = weight;
    }

    // for (int i = 1; i <= v_num; i++) {
    //     for (int j = 1; j <= v_num; j++)
    //         if (G->vmatrix[i][j] == INT_MAX) {
    //             printf("%5s ", "inf");
    //         } else {
    //             printf("%5d ", G->vmatrix[i][j]);
    //         }
    //     printf("\n");
    // }
    // printf("\n");

    return 0;
}

bool Floyd(struct graph *Graph, int **D)
{
    int i, j, k;

    for (i = 1; i <= Graph->Nv; i++) {
        for (j = 1; j <= Graph->Nv; j++) {
            D[i][j] = Graph->vmatrix[i][j];
        }
    }

    for (k = 1; k <= Graph->Nv; k++) {
        for (i = 1; i <= Graph->Nv; i++) {
            for (j = 1; j <= Graph->Nv; j++) {
                // means no exist such path
                if (D[i][k] == INT_MAX || D[k][j] == INT_MAX)
                    continue;

                if (D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    if (i == j && D[i][j] < 0) {
                        printf("%d %d\n", i, j);
                        return false;
                    }
                }
            }
        }
    }

    // for (int i = 1; i <= Graph->Nv; i++) {
    //     for (int j = 1; j <= Graph->Nv; j++)
    //         if (D[i][j] == INT_MAX) {
    //             printf("%5s ", "inf");
    //         } else {
    //             printf("%5d ", D[i][j]);
    //         }
    //     printf("\n");
    // }
    // printf("\n");

    return true;
}

int findMaxDist(int **dist, int v_num, int i)
{
    int max_dist = 0;

    for (int j = 1; j <= v_num; j++) {
        if (dist[i][j] > max_dist) {
            max_dist = dist[i][j];
        }
    }

    return max_dist;
}

int main(void)
{
    int v_num, e_num;
    scanf("%d %d\n", &v_num, &e_num);

    struct graph *G = create_graph(v_num);
    insert_edge(G, e_num);

    int **dist = malloc(sizeof(int *) * (v_num + 1));
    for (int i = 1; i <= v_num; i++) {
        dist[i] = malloc(sizeof(int) * (v_num + 1));
    }

    Floyd(G, dist);

    int max_dist = 0;
    int min_path = INT_MAX;
    int min_v = 0;

    for (int i = 1; i <= v_num; i++) {
        max_dist = findMaxDist(dist, v_num, i);
        if (max_dist == INT_MAX) {
            // vertex no link with the other, stop it
            printf("0\n");
            break;
        }

        if (max_dist < min_path) {
            min_path = max_dist;
            min_v = i;
        }
    }

    if (min_path != INT_MAX)
        printf("%d %d\n", min_v, min_path);

    return 0;
}
