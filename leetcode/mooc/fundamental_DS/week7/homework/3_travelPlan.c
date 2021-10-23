#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct graph {
    int Nv;
    int Ne;
    int **dist;
    int **cost;
};

int insert_edge(struct graph *G, int e_num)
{
    int v, w, dist, cost;
    for (int i = 0; i < e_num; i++) {
        scanf("%d %d %d %d\n", &v, &w, &dist, &cost);

        G->dist[v][w] = dist;
        G->dist[w][v] = dist;

        G->cost[v][w] = cost;
        G->cost[w][v] = cost;
    }

    // for (int i = 1; i <= v_num; i++) {
    //     for (int j = 1; j <= v_num; j++)
    //         if (G->dist[i][j] == INT_MAX) {
    //             printf("%5s ", "inf");
    //         } else {
    //             printf("%5d ", G->dist[i][j]);
    //         }
    //     printf("\n");
    // }
    // printf("\n");

    return 0;
}

struct graph *create_graph(int v_num, int e_num)
{
    struct graph *G = malloc(sizeof(struct graph));

    G->Nv = v_num;
    G->Ne = e_num;
    G->dist = malloc(sizeof(int *) * v_num);
    G->cost = malloc(sizeof(int *) * v_num);

    for (int i = 0; i < v_num; i++) {
        G->dist[i] = malloc(sizeof(int) * v_num);
        G->cost[i] = malloc(sizeof(int) * v_num);

        for (int j = 0; j < v_num; j++) {
            if (i == j) {
                // circle self
                G->dist[i][j] = 0;
                G->cost[i][j] = 0;
            } else {
                G->dist[i][j] = INT_MAX;
                G->cost[i][j] = INT_MAX;
            }
        }
    }

    insert_edge(G, e_num);
    return G;
}

int FindMinDist(struct graph *Graph, int *dist, int *collected)
{
    int MinV, V;
    int MinDist = INT_MAX;

    for (V = 0; V < Graph->Nv; V++) {
        if (collected[V] == false && dist[V] < MinDist) {
            MinDist = dist[V];
            MinV = V;
        }
    }

    if (MinDist < INT_MAX)
        return MinV;
    else
        return -1;
}

bool Dijkstra(struct graph *Graph, int dist[], int path[], int cost[], int S)
{
    int collected[Graph->Nv];
    int V, W;

    for (V = 0; V < Graph->Nv; V++) {
        dist[V] = Graph->dist[S][V];
        cost[V] = Graph->cost[S][V];
        if (dist[V] < INT_MAX)
            path[V] = S;
        else
            path[V] = -1;
        collected[V] = false;
    }

    path[S] = -1;
    collected[S] = true;

    while (1) {
        V = FindMinDist(Graph, dist, collected);
        if (V == -1)
            break;

        collected[V] = true;

        for (W = 0; W < Graph->Nv; W++) {
            if (collected[W] == false && Graph->dist[V][W] < INT_MAX) {
                if (Graph->dist[V][W] < 0)
                    return false;

                if (dist[V] + Graph->dist[V][W] < dist[W]) {
                    dist[W] = dist[V] + Graph->dist[V][W];
                    cost[W] = cost[V] + Graph->cost[V][W];
                    path[W] = V;
                    // printf("%d cost[%d] = %d\n", __LINE__, W, cost[W]);

                } else if ((dist[V] + Graph->dist[V][W] == dist[W])
                        && (cost[V] + Graph->cost[V][W] < cost[W])) {
                    cost[W] = cost[V] + Graph->cost[V][W];
                    path[W] = V;
                    // printf("%d cost[%d] = %d\n", __LINE__, W, cost[W]);
                }
            }
        }
    }

    return true;
}

int main(void)
{
    int v_num, e_num, src, dest;
    scanf("%d %d %d %d\n", &v_num, &e_num, &src, &dest);

    struct graph *g = create_graph(v_num, e_num);

    int *dist = malloc(sizeof(int) * v_num);
    int *path = malloc(sizeof(int) * v_num);
    int *cost = malloc(sizeof(int) * v_num);

    Dijkstra(g, dist, path, cost, src);
    printf("%d %d\n", dist[dest], cost[dest]);
    return 0;
}
