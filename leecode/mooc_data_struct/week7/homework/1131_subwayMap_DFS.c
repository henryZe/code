#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

#define MAX_CONJUNCTION 5
#define STOPS_NUM 10000

struct Vnode {
    int n_w;
    int w[MAX_CONJUNCTION * 2];
    int line[MAX_CONJUNCTION * 2];
};

struct graph {
    struct Vnode hash[STOPS_NUM];
};

int link_line(struct graph *g, int v, int w)
{
    for (int i = 0; i < g->hash[v].n_w; i++) {
        if (g->hash[v].w[i] == w) {
            return g->hash[v].line[i];
        }
    }
    assert(0);
    return -1;
}

int best_stop, best_line;
int visited[STOPS_NUM];

int path[STOPS_NUM];
int best_path[STOPS_NUM];

/*
 * 1. first print in a line the minimum number of stops.
 * 2. output the one with the minimum number of transfers.
 */
void DFS(struct graph *g, int V, int pre_line, int line_num, int stop_num, int e)
{
    if (stop_num > best_stop)
        return;

    if ((stop_num == best_stop) && (line_num > best_line))
        return;

    visited[V] = 1;
    path[stop_num] = V;

    if (V == e) {
        best_stop = stop_num;
        best_line = line_num;

        for (int tmp = 0; tmp <= stop_num; tmp++)
            best_path[tmp] = path[tmp];
    }

    struct Vnode *v = &g->hash[V];
    for (int i = 0; i < v->n_w; i++) {
        int W = v->w[i];

        if (!visited[W]) {
            int cur_line = link_line(g, V, W);

            if (pre_line != cur_line)
                DFS(g, W, cur_line, line_num + 1, stop_num + 1, e);
            else
                DFS(g, W, cur_line, line_num, stop_num + 1, e);
        }
    }

    // resume this vertex
    visited[V] = 0;
}

struct graph *create_graph(void)
{
    struct graph *g = malloc(sizeof(struct graph));

    // init
    for (int i = 0; i < STOPS_NUM; i++) {
        g->hash[i].n_w = 0;
    }

    int n_line;
    scanf("%d\n", &n_line);

    for (int i = 1; i <= n_line; i++) {
        int n_stop;
        scanf("%d ", &n_stop);

        int cur, pre;
        scanf("%d ", &pre);
        for (int j = 1; j < n_stop; j++) {
            scanf("%d ", &cur);

            g->hash[cur].line[g->hash[cur].n_w] = i;
            g->hash[pre].line[g->hash[pre].n_w] = i;

            g->hash[cur].w[g->hash[cur].n_w++] = pre;
            g->hash[pre].w[g->hash[pre].n_w++] = cur;

            pre = cur;
        }
    }

    return g;
}

int main(void)
{
    struct graph *g = create_graph();

    int cases;
    scanf("%d\n", &cases);

    for (int i = 0; i < cases; i++) {
        int s, e;
        scanf("%d %d\n", &s, &e);

        best_stop = INT_MAX;
        best_line = INT_MAX;
        DFS(g, s, -1, 0, 0, e);

        printf("%d\n", best_stop);
        // printf("%d\n", best_line);

        // printf("best path:\n");
        // for (int tmp = 0; tmp <= best_stop; tmp++) {
        //     printf("%d->", best_path[tmp]);
        // }
        // printf("\n");

        int begin = s;
        int pre_line = link_line(g, s, best_path[1]);

        for (int tmp = 1; tmp <= best_stop; tmp++) {
            int cur_line = link_line(g, best_path[tmp - 1], best_path[tmp]);

            // transfer
            if (pre_line != cur_line) {
                printf("Take Line#%d from %04d to %04d.\n",
                        pre_line, begin, best_path[tmp - 1]);

                begin = best_path[tmp - 1];
                pre_line = cur_line;
            }
        }
        // at the end
        printf("Take Line#%d from %04d to %04d.\n", pre_line, begin, e);
    }

    return 0;
}
