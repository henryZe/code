#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct graph {
    int Nv;
    int Ne;
    int *rescue;
    int **dist;
};

int insert_edge(struct graph *G, int e_num)
{
    int v, w, dist;
    for (int i = 0; i < e_num; i++) {
        scanf("%d %d %d\n", &v, &w, &dist);

        G->dist[v][w] = dist;
        G->dist[w][v] = dist;
    }

    return 0;
}

struct graph *create_graph(int v_num, int e_num)
{
    struct graph *G = malloc(sizeof(struct graph));

    G->Nv = v_num;
    G->Ne = e_num;
    G->rescue = malloc(sizeof(int) * v_num);
    G->dist = malloc(sizeof(int *) * v_num);

    for (int i = 0; i < v_num; i++) {
        scanf("%d ", G->rescue + i);
    }

    for (int i = 0; i < v_num; i++) {
        G->dist[i] = malloc(sizeof(int) * v_num);

        for (int j = 0; j < v_num; j++) {
            if (i == j) {
                // circle self
                G->dist[i][j] = 0;
            } else {
                G->dist[i][j] = INT_MAX;
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

int Dijkstra(struct graph *Graph, int dist[], int path[], int rescue[], int S, int E)
{
    int collected[Graph->Nv];
    int count[Graph->Nv];
    int V, W;

    for (V = 0; V < Graph->Nv; V++) {
        dist[V] = Graph->dist[S][V];
        rescue[V] = Graph->rescue[V];
        count[V] = 0;

        if (dist[V] < INT_MAX)
            path[V] = S;
        else
            path[V] = -1;
        collected[V] = false;
    }

    path[S] = -1;
    collected[S] = true;
    count[S] = 1;

    for (V = 0; V < Graph->Nv; V++) {
        if (collected[V] == false && dist[V] < INT_MAX) {
            rescue[V] += rescue[S];
            count[V] = count[S];
        }
    }

    while (1) {
        if (collected[E])
            // stop searching
            break;

        V = FindMinDist(Graph, dist, collected);
        if (V == -1)
            break;

        collected[V] = true;

        for (W = 0; W < Graph->Nv; W++) {
            if (collected[W] == false && Graph->dist[V][W] < INT_MAX) {
                if (dist[V] + Graph->dist[V][W] < dist[W]) {
                    dist[W] = dist[V] + Graph->dist[V][W];
                    rescue[W] = rescue[V] + Graph->rescue[W];
                    path[W] = V;
                    count[W] = count[V];

                } else if ((dist[V] + Graph->dist[V][W] == dist[W])
                    && (rescue[V] + Graph->rescue[W] > rescue[W])) {
                    rescue[W] = rescue[V] + Graph->rescue[W];
                    path[W] = V;
                    count[W] += count[V];

                }
            }
        }
    }

    return count[E];
}

int main(void)
{
    int start, end, v_num, e_num;
    scanf("%d %d %d %d\n", &v_num, &e_num, &start, &end);

    int *rescue = malloc(sizeof(int) * v_num);
    int *dist = malloc(sizeof(int) * v_num);
    int *path = malloc(sizeof(int) * v_num);

    struct graph *g = create_graph(v_num, e_num);
    int num = Dijkstra(g, dist, path, rescue, start, end);
    printf("%d %d\n", num, rescue[end]);

    return 0;
}
