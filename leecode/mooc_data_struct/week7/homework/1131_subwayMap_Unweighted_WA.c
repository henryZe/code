#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_CONJUNCTION 5
#define STOPS_NUM 10000

struct Vnode {
    int n_line;
    int n_w;
    int line[MAX_CONJUNCTION];
    int w[MAX_CONJUNCTION * 2];
};

struct graph {
    int Nv;
    struct Vnode hash[STOPS_NUM];
};

struct queue {
    int *queue;
    int size;
    int front;
    int rear;
};

struct queue *queue_create(int size)
{
    struct queue *q = malloc(sizeof(struct queue));

    q->queue = malloc(sizeof(int) * size);
    q->size = size;
    q->front = q->rear = 0;

    return q;
}

bool isEmpty(struct queue *q)
{
    return q->rear == q->front;
}

bool isFull(struct queue *q)
{
    return q->rear == (q->front - 1);
}

int enqueue(struct queue *q, int v)
{
    if (isFull(q)) {
        return -1;
    }

    q->queue[q->rear] = v;
    q->rear = (q->rear + 1) % q->size;
    return 0;
}

int dequeue(struct queue *q)
{
    int v;

    if (isFull(q)) {
        return -1;
    }

    v = q->queue[q->front];
    q->front = (q->front + 1) % q->size;
    return v;
}

int link_line(struct graph *g, int v, int w)
{
    for (int i = 0; i < g->hash[v].n_line; i++) {
        for (int j = 0; j < g->hash[w].n_line; j++) {
            if (g->hash[v].line[i] == g->hash[w].line[j])
                return g->hash[v].line[i];
        }
    }

    return -1;
}

/*
 * 1. first print in a line the minimum number of stops.
 * 2. output the one with the minimum number of transfers.
 */
int Unweighted(struct graph *g, int s, int e, int path[], int line[])
{
    int dist[STOPS_NUM];
    int count[STOPS_NUM];

    for (int i = 0; i < STOPS_NUM; i++) {
        path[i] = -1;
        dist[i] = INT_MAX;
        line[i] = -1;
        count[i] = 0;
    }

    struct queue *Q = queue_create(g->Nv);

    enqueue(Q, s);
    dist[s] = 0;

    while (!isEmpty(Q)) {
        if (dist[e] != INT_MAX)
            break;

        int V = dequeue(Q);
        struct Vnode *v = &g->hash[V];

        for (int i = 0; i < v->n_w; i++) {
            int W = v->w[i];

            if (dist[W] == INT_MAX) {
                dist[W] = dist[V] + 1;
                path[W] = V;

                line[W] = link_line(g, V, W);
                count[W] = line[V] != line[W] ? count[V] + 1 : count[V];

                enqueue(Q, W);

            } else if (dist[W] == dist[V] + 1) {
                int tmp_line = link_line(g, V, W);
                int tmp_count = line[V] != tmp_line ? count[V] + 1 : count[V];

                if (count[W] > tmp_count) {
                    path[W] = V;

                    line[W] = tmp_line;
                    count[W] = tmp_count;

                    enqueue(Q, W);

                }
                // Assert!!!: There exists multiple local optimal solutions, not unique.
                else if (count[W] == tmp_count) {
                    printf("Error: Old V %04d W %04d\n", path[W], W);
                    printf("Error: New V %04d W %04d\n", V, W);

                    // void (*func)(void) = NULL;
                    // func();

                    // path[W] = V;
                    // line[W] = tmp_line;

                    // enqueue(Q, W);
                }
            }
        }
    }

    // printf("count[%d] = %d\n", e, count[e]);
    return dist[e];
}

struct graph *create_graph(void)
{
    struct graph *g = malloc(sizeof(struct graph));
    g->Nv = 0;

    // init
    for (int i = 0; i < STOPS_NUM; i++) {
        g->hash[i].n_line = 0;
        g->hash[i].n_w = 0;
    }

    int n_line;
    scanf("%d\n", &n_line);

    for (int i = 1; i <= n_line; i++) {
        int ith_line, pre = -1;
        scanf("%d ", &ith_line);

        for (int j = 0; j < ith_line; j++) {
            int cur;
            scanf("%d ", &cur);

            g->Nv++;
            if (!(g->hash[cur].n_line &&
                g->hash[cur].line[g->hash[cur].n_line - 1] == i)) {
                // not circle head & tail
                g->hash[cur].line[g->hash[cur].n_line++] = i;
            }
            if (pre >= 0) {
                g->hash[cur].w[g->hash[cur].n_w++] = pre;
                g->hash[pre].w[g->hash[pre].n_w++] = cur;
            }
            pre = cur;
        }
    }

    return g;
}

void reverse_path(struct graph *g, int pre, int e, int *path)
{
    if (e == -1)
        return;

    reverse_path(g, e, path[e], path);
    path[e] = pre;
}

int main(void)
{
    struct graph *g = create_graph();

    int cases;
    scanf("%d\n", &cases);

    int path[STOPS_NUM];
    int line[STOPS_NUM];

    for (int i = 0; i < cases; i++) {
        int s, e;
        scanf("%d %d\n", &s, &e);

        int count = Unweighted(g, s, e, path, line);

        reverse_path(g, -1, e, path);

        printf("%d\n", count);

        int begin = s;
        int pre_stop = s;
        int pre_line = line[path[s]];

        for (int tmp = path[s]; tmp != -1; tmp = path[tmp]) {
            if (pre_line != line[tmp]) {
                printf("Take Line#%d from %04d to %04d.\n", pre_line, begin, pre_stop);
                begin = pre_stop;
                pre_line = line[tmp];
            }
            pre_stop = tmp;
        }
        // at the end
        printf("Take Line#%d from %04d to %04d.\n", pre_line, begin, pre_stop);
    }

    return 0;
}