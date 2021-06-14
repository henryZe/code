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

struct stack {
    int *data;
    int top;
    int size;
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

int stack_init(struct stack *s, int stack_size)
{
    if (!s)
        return 0;

    s->top = 0;
    s->size = stack_size;
    s->data = malloc(sizeof(int) * stack_size);
    return 0;
}

bool stack_empty(struct stack *s)
{
    return s->top == 0;
}

bool stack_full(struct stack *s)
{
    return s->top == s->size;
}

bool stack_push(struct stack *s, int num)
{
    if (stack_full(s))
        return false;

    s->data[(s->top)++] = num;
    return true;
}

int stack_pop(struct stack *s)
{
    if (stack_empty(s))
        return -1;
    return s->data[--(s->top)];
}

int min_send = INT_MAX, min_back = INT_MAX;
int *best_path;
int *visited;

/*
 * 2. the one that requires the least number of bikes sent from PBMC will be chosen.
 * 3. output the one that requires minimum number of bikes that we must take back to PBMC.
 */
void dfs(struct stack *s, int **path, int *indegree, int w, int src, int num, int *capacity)
{
    stack_push(s, w);
    visited[w] = true;

    if (w == src) {
        int send = 0, back = 0;

        for (int i = s->top - 2; i >= 0; i--) {
            int c = capacity[s->data[i]];

            if (back + c >= capacity[PERFECT]) {
                back += c - capacity[PERFECT];
            } else {
                send += capacity[PERFECT] - back - c;
                back = 0;
            }
        }

        // 遍历所有路径，最后比较最优结果
        if (send > min_send)
            goto end;

        if (send == min_send && back >= min_back)
            goto end;

        min_send = send;
        min_back = back;
        for (int i = s->top - 1, j = 0; i >= 0; i--, j++) {
            best_path[j] = s->data[i];
        }

        goto end;
    }

    for (int i = 0; i < indegree[w]; i++) {
        int v = path[w][i];
        if (visited[v])
            continue;

        dfs(s, path, indegree, v, src, num + 1, capacity);
    }

end:
    visited[w] = false;
    stack_pop(s);
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

    best_path = malloc(sizeof(int) * (v_num + 1));
    visited = malloc(sizeof(int) * (v_num + 1));
    for (int i = 0; i <= v_num; i++) {
        visited[i] = false;
    }

    struct stack s;
    stack_init(&s, v_num + 1);
    dfs(&s, path, indegree, dest, src, 0, capacity);

    printf("%d ", min_send);
    int i;
    for (i = 0; best_path[i] != dest; i++) {
        printf("%d->", best_path[i]);
    }
    printf("%d ", best_path[i]);
    printf("%d\n", min_back);

    return 0;
}
