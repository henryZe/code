#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

#define QUEUE_SIZE 100

struct edge {
    int vertex;
    int time;
    struct edge *Next;  /* 指向下一个邻接点的指针 */
};

struct Vnode {
    /* 边表头指针 */
    struct edge FirstEdge;
};

struct Graph {
    int Nv;             /* 顶点数 */
    int Ne;             /* 边数   */
    struct Vnode *G;    /* 邻接表 */
};

struct queue {
    int queue[QUEUE_SIZE];
    int front;
    int rear;
};

struct queue *queue_create(void)
{
    struct queue *q = malloc(sizeof(struct queue));
    q->front = q->rear = 0;
    return q;
}

bool IsFull(struct queue *q)
{
    return q->rear == (q->front - 1);
}

bool IsEmpty(struct queue *q)
{
    return q->front == q->rear;
}

int Enqueue(struct queue *q, int node)
{
    if (IsFull(q)) {
        return -1;
    }

    q->queue[q->rear] = node;
    q->rear = (q->rear + 1) % QUEUE_SIZE;
    return 0;
}

int Dequeue(struct queue *q)
{
    int node;

    if (IsEmpty(q)) {
        return -1;
    }

    node = q->queue[q->front];
    q->front = (q->front + 1) % QUEUE_SIZE;
    return node;
}

void print_keyroute(struct Graph *G, int *Earliest, int *Latest)
{
    if (!Earliest || !Latest || !G) {
        return;
    }

    for (int i = 1; i <= G->Nv; i++) {
        for (struct edge *e = G->G[i].FirstEdge.Next; e; e = e->Next) {
            // printf("Latest[%d] %d, Earliest[%d] %d, time %d\n",
            //         e->vertex, Latest[e->vertex], i, Earliest[i], e->time);

            if (Latest[e->vertex] - Earliest[i] - e->time == 0) {
                printf("%d->%d\n", i, e->vertex);
            }
        }
    }

    return;
}

// AOE, activity on edge
int *TopSort(struct Graph *G, int *totalTime)
{
    int *Indegree = malloc(sizeof(int) * (G->Nv + 1));
    int *Earliest = malloc(sizeof(int) * (G->Nv + 1));
    struct queue *Q = queue_create();

    for (int i = 1; i <= G->Nv; i++) {
        Indegree[i] = 0;
        Earliest[i] = 0;
    }

    for (int i = 1; i <= G->Nv; i++) {
        for (struct edge *e = G->G[i].FirstEdge.Next; e; e = e->Next) {
            Indegree[e->vertex]++;
        }
    }

    for (int i = 1; i <= G->Nv; i++) {
        if (Indegree[i] == 0) {
            Enqueue(Q, i);
        }
    }

    int cnt = 0;
    int v, w;
    *totalTime = 0;
    while (!IsEmpty(Q)) {
        v = Dequeue(Q);
        cnt++;

        for (struct edge *e = G->G[v].FirstEdge.Next; e; e = e->Next) {
            w = e->vertex;

            if (Earliest[v] + e->time > Earliest[w]) {
                Earliest[w] = Earliest[v] + e->time;
                *totalTime = fmax(*totalTime, Earliest[w]);
            }

            if (--Indegree[w] == 0)
                Enqueue(Q, w);
        }
    }

    if (cnt != G->Nv)
        return NULL;

    printf("%d\n", *totalTime);
    return Earliest;
}

int insertEdge(struct Graph *g, int v, int w, int time)
{
    struct edge *v_edge;

    v_edge = malloc(sizeof(struct edge));
    v_edge->vertex = w;
    v_edge->time = time;

    // insert
    v_edge->Next = g->G[v].FirstEdge.Next;
    g->G[v].FirstEdge.Next = v_edge;

    return 0;
}

struct Graph *create_graph(int v_num, int e_num)
{
    int v, w, time;
    struct Graph *g = malloc(sizeof(struct Graph));

    g->Nv = v_num;
    g->Ne = e_num;
    g->G = malloc(sizeof(struct Vnode) * (v_num + 1));
    for (int i = 1; i <= v_num; i++) {
        g->G[i].FirstEdge.Next = NULL;
    }

    for (int i = 0; i < e_num; i++) {
        scanf("%d %d %d\n", &v, &w, &time);
        insertEdge(g, v, w, time);
    }

    return g;
}

// AOE, activity on edge
int *TopSort_outdegree(struct Graph *G, int *Earliest, int totalTime)
{
    int *Outdegree = malloc(sizeof(int) * (G->Nv + 1));
    int *Latest = malloc(sizeof(int) * (G->Nv + 1));
    struct queue *Q = queue_create();

    for (int i = 1; i <= G->Nv; i++) {
        Outdegree[i] = 0;
        Latest[i] = INT_MAX;
    }

    for (int i = 1; i <= G->Nv; i++) {
        for (struct edge *e = G->G[i].FirstEdge.Next; e; e = e->Next) {
            Outdegree[i]++;
        }
    }

    for (int i = 1; i <= G->Nv; i++) {
        if (Outdegree[i] == 0) {
            Enqueue(Q, i);
            // !!CAUTION: end point's latest time should be set as totalTime
            Latest[i] = totalTime;
        }
    }

    while (!IsEmpty(Q)) {
        int w = Dequeue(Q);

        for (int i = 1; i <= G->Nv; i++) {
            if (!Outdegree[i])
                continue;

            for (struct edge *e = G->G[i].FirstEdge.Next; e; e = e->Next) {
                if (e->vertex == w) {
                    if (Latest[w] - e->time < Latest[i])
                        Latest[i] = Latest[w] - e->time;

                    if (--Outdegree[i] == 0)
                        Enqueue(Q, i);

                    break;
                }
            }
        }
    }

    // for (int i = 1; i <= G->Nv; i++) {
    //     printf("i %d Outdegree %d Latest %d\n", i, Outdegree[i], Latest[i]);
    // }

    return Latest;
}

int main(void)
{
    int v_num, e_num, totalTime;
    scanf("%d %d\n", &v_num, &e_num);

    struct Graph *g = create_graph(v_num, e_num);

    int *Earliest = TopSort(g, &totalTime);
    if (!Earliest) {
        printf("0\n");
        return 0;
    }

    int *Latest = TopSort_outdegree(g, Earliest, totalTime);
    if (!Latest)
        return 0;

    print_keyroute(g, Earliest, Latest);
    return 0;
}