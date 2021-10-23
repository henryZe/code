#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define CITY_LEN 4
#define end_city "ROM"
#define Index(x) (x - 'A')

unsigned char Hash[26][26][26];

struct edge {
    int w;
    int cost;
    struct edge *Next;
};

struct Vnode {
    char city[CITY_LEN];
    int happiness;
    struct edge FirstEdge;
};

struct Graph {
    int Nv;             /* 顶点数 */
    int Ne;             /* 顶点数 */
    struct Vnode *G;    /* 邻接表 */
};

int hash(char *city)
{
    unsigned char *h = (void *)Hash;
    return &Hash[Index(city[0])][Index(city[1])][Index(city[2])] - h;
}

int insert_hash(char *city, int index)
{
    unsigned char *h = (void *)Hash;
    h[hash(city)] = index;
    return 0;
}

int find_hash(char *city)
{
    unsigned char *h = (void *)Hash;
    return h[hash(city)];
}

int FindMinDist(struct Graph *g, int *dist, int *collected)
{
    int MinV, V;
    int MinDist = INT_MAX;

    for (V = 0; V < g->Nv; V++) {
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

/*
 * 1. find the route with the least cost.
 * 2. the one with the maximum happiness.
 * 3. output the one with the maximum average happiness.
 */
int Dijkstra(struct Graph *g, int s, int e, int dist[], int path[], int happy[], int nodes[])
{
    int count[g->Nv];
    int collected[g->Nv];
    int V, W;

    for (int i = 0; i < g->Nv; i++) {
        count[i] = 0;
        collected[i] = false;
    }

    for (struct edge *e = g->G[s].FirstEdge.Next; e; e = e->Next) {
        count[e->w]++;
        dist[e->w] = e->cost;
        path[e->w] = s;
        happy[e->w] = g->G[e->w].happiness;
        nodes[e->w] = 1;
    }

    collected[s] = true;
    while (1) {
        if (collected[e] == true)
            break;

        V = FindMinDist(g, dist, collected);
        if (V == -1)
            break;

        collected[V] = true;

        for (struct edge *e = g->G[V].FirstEdge.Next; e; e = e->Next) {
            W = e->w;
            if (collected[W] == false) {
                if (dist[V] + e->cost < dist[W]) {
                    count[W] = count[V];

                    dist[W] = dist[V] + e->cost;
                    path[W] = V;
                    happy[W] = g->G[W].happiness + happy[V];
                    nodes[W] = nodes[V] + 1;

                } else if (dist[V] + e->cost == dist[W]) {
                    count[W] += count[V];

                    if (g->G[W].happiness + happy[V] > happy[W]) {
                        path[W] = V;
                        happy[W] = g->G[W].happiness + happy[V];
                        nodes[W] = nodes[V] + 1;

                    } else if (g->G[W].happiness + happy[V] == happy[W]) {
                        if (nodes[V] + 1 < nodes[W]) {
                            path[W] = V;
                            nodes[W] = nodes[V] + 1;
                        }
                    }
                }
            }
        }
    }

    // for (int i = 0; i < g->Nv; i++) {
    //     printf("count[%d] = %d\n", i, count[i]);
    //     printf("dist[%d] = %d\n", i, dist[i]);
    //     printf("path[%d] = %d\n", i, path[i]);
    // }

    return count[e];
}

struct Graph *create_graph(int v_num, int e_num)
{
    struct Graph *g = malloc(sizeof(struct Graph));

    g->Nv = 0;
    g->Ne = e_num;
    g->G = malloc(sizeof(struct Vnode) * v_num);

    for (int i = 0; i < v_num; i++) {
        g->G[i].FirstEdge.Next = NULL;
    }

    return g;
}

int insert_vertex(struct Graph *g, char *city, int happiness)
{
    int i = g->Nv++;

    memcpy(g->G[i].city, city, CITY_LEN + 1);
    g->G[i].happiness = happiness;

    return i;
}

int insert_edge(struct Graph *g, int v, int w, int cost)
{
    struct edge *e = malloc(sizeof(struct edge));

    e->w = w;
    e->cost = cost;
    e->Next = g->G[v].FirstEdge.Next;
    g->G[v].FirstEdge.Next = e;

    return 0;
}

void distplay_path(struct Graph *g, int *path, int e)
{
    if (path[e] == -1)
        return;

    distplay_path(g, path, path[e]);
    printf("->%s", g->G[e].city);

    // while (e != -1) {
    //     printf("%s->", g->G[e].city);
    //     e = path[e];
    // }
    // printf("\n");
}

int main(void)
{
    int n_city, n_road;
    char start_city[CITY_LEN];
    scanf("%d %d %s\n", &n_city, &n_road, start_city);

    struct Graph *g = create_graph(n_city, n_road);

    char city[CITY_LEN];
    int happiness;

    int index = insert_vertex(g, start_city, 0);
    insert_hash(start_city, index);

    for (int i = 1; i < n_city; i++) {
        scanf("%s %d\n", city, &happiness);
        index = insert_vertex(g, city, happiness);
        insert_hash(city, index);
    }

    char cityA[CITY_LEN];
    char cityB[CITY_LEN];
    int cost;

    for (int i = 0; i < n_road; i++) {
        scanf("%s %s %d\n", cityA, cityB, &cost);

        int indexA = find_hash(cityA);
        int indexB = find_hash(cityB);

        insert_edge(g, indexA, indexB, cost);
        insert_edge(g, indexB, indexA, cost);
    }

    // for (int i = 0; i < g->Nv; i++) {
    //     printf("%s:\n", g->G[i].city);
    //     for (struct edge *e = g->G[i].FirstEdge.Next; e; e = e->Next)
    //         printf("%s ", g->G[e->w].city);
    //     printf("\n");
    // }

    int s = find_hash(start_city);
    int e = find_hash(end_city);
    int *dist = malloc(sizeof(int) * n_city);
    int *path = malloc(sizeof(int) * n_city);
    int *happy = malloc(sizeof(int) * n_city);
    int *nodes = malloc(sizeof(int) * n_city);

    for (int i = 0; i < n_city; i++) {
        dist[i] = INT_MAX;
        path[i] = -1;
        happy[i] = 0;
        nodes[i] = 0;
    }

    int count = Dijkstra(g, s, e, dist, path, happy, nodes);

    printf("%d %d %d %d\n", count, dist[e], happy[e], happy[e]/nodes[e]);
    printf("%s", g->G[s].city);
    distplay_path(g, path, e);
    printf("\n");

    return 0;
}