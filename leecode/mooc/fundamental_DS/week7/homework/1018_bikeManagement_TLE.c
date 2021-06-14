#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct edge {
    int w;
    int dist;
    struct edge *next;
};

struct vertex {
    struct edge head;
};

struct graph {
    int Nv;
    struct vertex *v;
};

#define PERFECT 0

int FindMinDist(struct graph *g, int *dist, int *collected)
{
    int MinV = -1;
    int MinDist = INT_MAX;

    for (int V = 0; V < g->Nv; V++) {
        if (collected[V] == false && dist[V] < MinDist) {
            MinDist = dist[V];
            MinV = V;
        }
    }

    return MinV;
}

/*
 * 1. PBMC will always choose the shortest path to reach that station.
 */
void Dijkstra(struct graph *g, int src, int *indegree, int **path)
{
    int dist[g->Nv];
    int collected[g->Nv];

    for (int i = 0; i < g->Nv; i++) {
        dist[i] = INT_MAX;
        collected[i] = false;
        indegree[i] = 0;
    }

    for (struct edge *e = g->v[src].head.next; e; e = e->next) {
        dist[e->w] = e->dist;
        path[e->w][0] = src;
        indegree[e->w]++;
    }

    dist[src] = 0;
    collected[src] = true;

    int v, w;
    while (1) {
        v = FindMinDist(g, dist, collected);
        if (v == -1)
            break;

        collected[v] = true;

        for (struct edge *e = g->v[v].head.next; e; e = e->next) {
            w = e->w;
            if (collected[w] == false) {
                if (dist[w] > dist[v] + e->dist) {
                    dist[w] = dist[v] + e->dist;
                    path[w][0] = v;
                    indegree[w] = 1;
                } else if (dist[w] == dist[v] + e->dist) {
                    path[w][indegree[w]++] = v;
                }
            }
        }
    }
}

struct graph *create_graph(int v_num)
{
    struct graph *g = malloc(sizeof(struct graph));

    g->Nv = v_num;
    g->v = malloc(sizeof(struct vertex) * v_num);

    return g;
}

int insert_edge(struct graph *g, int v, int w, int dist)
{
    struct edge *e = malloc(sizeof(struct edge));

    e->w = w;
    e->dist = dist;
    e->next = g->v[v].head.next;

    g->v[v].head.next = e;

    return 0;
}

int min_send = INT_MIN, min_back = INT_MAX;
int *best_path;

int *cur_path;
int *visited;

/*
 * 2. the one that requires the least number of bikes sent from PBMC will be chosen.
 * 3. output the one that requires minimum number of bikes that we must take back to PBMC.
 */
void dfs(struct graph *g, int v, int dest, int num, int send, int back, int *capacity)
{
    visited[v] = true;
    cur_path[num++] = v;

    if (v == dest) {
        // 遍历所有路径，最后比较最优结果
        if (send < min_send)
            goto end;

        if (send == min_send && back >= min_back)
            goto end;

        min_send = send;
        min_back = back;
        for (int i = 0; i < num; i++) {
            best_path[i] = cur_path[i];
        }

        // printf("min_send %d min_back %d num %d\n",
        //         min_send, min_back, num);
        goto end;
    }

    // printf("v %d num %d send %d back %d\n",
    //         v, num, send, back);

    int w, new_send, new_back, c;
    for (struct edge *e = g->v[v].head.next; e; e = e->next) {
        w = e->w;

        if (visited[w]) {
            continue;
        }

        c = capacity[w];

        if (c >= capacity[PERFECT]) {
            new_back = back + c - capacity[PERFECT];

            // printf("v->w %d->%d num %d send %d back %d\n",
            //         v, w, num, new_send, new_back);

            dfs(g, w, dest, num, send, new_back, capacity);

        } else {
            if (back + c >= capacity[PERFECT]) {
                new_back = back + c - capacity[PERFECT];
                new_send = send;
            } else {
                new_back = 0;
                new_send = send + back + c - capacity[PERFECT];
            }

            // printf("v->w %d->%d num %d send %d back %d\n",
            //         v, w, num, new_send, new_back);

            dfs(g, w, dest, num, new_send, new_back, capacity);
        }
    }

end:
    visited[v] = false;
}

void insert_edge_iterate(struct graph *g, int w, int *indegree, int **path)
{
    int v;

    for (int i = 0; i < indegree[w]; i++) {
        v = path[w][i];
        insert_edge(g, v, w, 0);
        insert_edge_iterate(g, v, indegree, path);
    }
}

int main(void)
{
    int max_capacity, v_num, dest, e_num, src = 0;
    scanf("%d %d %d %d\n", &max_capacity, &v_num, &dest, &e_num);

    struct graph *g = create_graph(v_num + 1);

    int *capacity = malloc(sizeof(int) * (v_num + 1));
    capacity[0] = max_capacity / 2;
    for (int i = 1; i <= v_num; i++) {
        scanf("%d ", capacity + i);
    }

    int v, w, dist;
    for (int i = 0; i < e_num; i++) {
        scanf("%d %d %d\n", &v, &w, &dist);
        insert_edge(g, v, w, dist);
        insert_edge(g, w, v, dist);
    }

    int *indegree = malloc(sizeof(int) * (v_num + 1));
    int **path = malloc(sizeof(int *) * (v_num + 1));
    for (int i = 0; i <= v_num; i++) {
        path[i] = malloc(sizeof(int *) * (v_num + 1));
    }

    Dijkstra(g, src, indegree, path);

    struct graph *path_g = create_graph(v_num + 1);
    insert_edge_iterate(path_g, dest, indegree, path);

    best_path = malloc(sizeof(int) * (v_num + 1));
    cur_path = malloc(sizeof(int) * (v_num + 1));
    visited = malloc(sizeof(int) * (v_num + 1));
    for (int i = 0; i <= v_num; i++) {
        visited[i] = false;
    }

    dfs(path_g, src, dest, 0, 0, 0, capacity);

    printf("%d ", -min_send);
    int i;
    for (i = 0; best_path[i] != dest; i++) {
        printf("%d->", best_path[i]);
    }
    printf("%d ", best_path[i]);
    printf("%d\n", min_back);

    return 0;
}
