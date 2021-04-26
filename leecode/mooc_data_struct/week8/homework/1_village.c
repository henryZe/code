#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

struct graph {
    int Nv;
    int Ne;
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

    return 0;
}

int findMinDist(struct graph *G, int *dist)
{
    int minV;
    int minDist = INT_MAX;

    for (int v = 1; v <= G->Nv; v++) {
        if (dist[v] && dist[v] < minDist) {
            minDist = dist[v];
            minV = v;
        }
    }

    if (minDist == INT_MAX)
        return -1;

    return minV;
}

int Prim(struct graph *G)
{
    int *dist = malloc(sizeof(int) * (G->Nv + 1));
    int totalWeight = 0;
    int Vcount = 0;

    for (int v = 1; v <= G->Nv; v++) {
        dist[v] = G->vmatrix[1][v];
    }

    dist[1] = 0;
    Vcount++;

    while (1) {
        int v = findMinDist(G, dist);
        if (v < 0)
            break;

        totalWeight += dist[v];
        dist[v] = 0;
        Vcount++;

        for (int w = 1; w <= G->Nv; w++) {
            if (dist[w] && G->vmatrix[v][w] < INT_MAX) {
                if (G->vmatrix[v][w] < dist[w]) {
                    dist[w] = G->vmatrix[v][w];
                }
            }
        }
    }

    // could not generate the MST
    if (Vcount < G->Nv)
        return -1;

    return totalWeight;
}

int main(void)
{
    int v_num, e_num;
    scanf("%d %d\n", &v_num, &e_num);

    struct graph *g = create_graph(v_num);
    insert_edge(g, e_num);

    printf("%d\n", Prim(g));
    return 0;
}
