#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

struct graph {
    int Nv;
    int **dist;
};

int FindMinDist(struct graph *Graph, int *dist, int *collected)
{
    int MinV, V;
    int MinDist = INT_MAX;

    for (V = 1; V <= Graph->Nv; V++) {
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

void Dijkstra(struct graph *Graph, int dist[], int S)
{
    int collected[Graph->Nv + 1];
    int V, W;

    for (V = 1; V <= Graph->Nv; V++) {
        dist[V] = Graph->dist[S][V];
        collected[V] = false;
    }

    collected[S] = true;
    while (1) {
        V = FindMinDist(Graph, dist, collected);
        if (V == -1)
            break;

        collected[V] = true;

        for (W = 1; W <= Graph->Nv; W++) {
            if (collected[W] == false && Graph->dist[V][W] < INT_MAX) {
                if (dist[V] + Graph->dist[V][W] < dist[W]) {
                    dist[W] = dist[V] + Graph->dist[V][W];
                }
            }
        }
    }

    // for (int i = 1; i <= Graph->Nv; i++) {
    //     printf("S %d dist[%d] = %d\n", S, i, dist[i]);
    // }
}

int n_house;

int getIndex(char *string)
{
    if (string[0] == 'G')
        return atoi(string + 1) + n_house;
    else
        return atoi(string); 
}

int insert_edge(struct graph *G, int e_num)
{
    char a[10], b[10];
    int v, w, dist;

    for (int i = 0; i < e_num; i++) {
        scanf("%s %s %d\n", a, b, &dist);

        v = getIndex(a);
        w = getIndex(b);

        G->dist[v][w] = dist;
        G->dist[w][v] = dist;
    }

    // for (int i = 1; i <= G->Nv; i++) {
    //     for (int j = 1; j <= G->Nv; j++) {
    //         if (G->dist[i][j] == INT_MAX)
    //             printf("- ");
    //         else
    //             printf("%d ", G->dist[i][j]);
    //     }
    //     printf("\n");
    // }

    return 0;
}

struct graph *create_graph(int v_num, int e_num)
{
    struct graph *G = malloc(sizeof(struct graph));

    G->Nv = v_num;
    G->dist = malloc(sizeof(int *) * (v_num + 1));

    for (int i = 1; i <= v_num; i++) {
        G->dist[i] = malloc(sizeof(int) * (v_num + 1));

        for (int j = 1; j <= v_num; j++) {
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

/*
 * Conditions:
 * 1. it must guarantee that all the houses are in its service range.
 * 2. minimum distance between the station and any of the residential housing is as far away as possible.
 * 3. output the one with the smallest average distance to all the houses.
 * 4. output the one with the smallest index number.
 */
int main(void)
{
    int n_candidate, n_road, d_range;
    scanf("%d %d %d %d\n", &n_house, &n_candidate, &n_road, &d_range);

    // matrix
    struct graph *g = create_graph(n_house + n_candidate, n_road);

    int cur = 0, min_dist = 0, sum_dist = INT_MAX;
    int *dist = malloc(sizeof(int) * (n_house + n_candidate + 1));

    for (int i = 1; i <= n_candidate; i++) {
        for (int j = 1; j <= (n_house + n_candidate); j++) {
            dist[j] = INT_MAX;
        }

        Dijkstra(g, dist, n_house + i);

        int cur_sum = 0, cur_min = INT_MAX;
        for (int j = 1; j <= n_house; j++) {
            if (dist[j] > d_range) {
                cur_min = INT_MAX;
                break;
            }

            if (cur_min > dist[j])
                cur_min = dist[j];

            cur_sum += dist[j];
        }

        // printf("i %d cur_min %d cur_sum %d\n", i, cur_min, cur_sum);

        if (cur_min == INT_MAX)
            continue;

        if (cur_min > min_dist) {
            min_dist = cur_min;
            sum_dist = cur_sum;
            cur = i;
        } else if (cur_min == min_dist) {
            if (cur_sum < sum_dist) {
                sum_dist = cur_sum;
                cur = i;
            }
        }
    }

    if (!cur) {
        printf("No Solution\n");
        return 0;
    }

    printf("G%d\n", cur);
    printf("%.1f %.1f\n", (double)min_dist, (double)sum_dist/n_house);
    return 0;
}