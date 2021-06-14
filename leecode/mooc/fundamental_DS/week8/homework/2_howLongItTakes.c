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

// AOE, activity on edge
int TopSort(struct Graph *G)
{
    int totalTime = 0;
    int *Indegree = malloc(sizeof(int) * G->Nv);
    int *Earliest = malloc(sizeof(int) * G->Nv);
    struct queue *Q = queue_create();

    for (int i = 0; i < G->Nv; i++) {
        Indegree[i] = 0;
        Earliest[i] = 0;
    }

    for (int i = 0; i < G->Nv; i++) {
        for (struct edge *e = G->G[i].FirstEdge.Next; e; e = e->Next) {
            Indegree[e->vertex]++;
        }
    }

    for (int i = 0; i < G->Nv; i++) {
        if (Indegree[i] == 0) {
            Enqueue(Q, i);
        }
    }

    int cnt = 0;
    int w;
    struct edge *e;
    while (!IsEmpty(Q)) {
        int v = Dequeue(Q);
        cnt++;

        for (e = G->G[v].FirstEdge.Next; e; e = e->Next) {
            w = e->vertex;

            if (Earliest[v] + e->time > Earliest[w]) {
                Earliest[w] = Earliest[v] + e->time;
                totalTime = fmax(totalTime, Earliest[w]);
            }

            if (--Indegree[w] == 0)
                Enqueue(Q, w);
        }
    }

    if (cnt != G->Nv)
        return -1;

    return totalTime;
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
    g->G = malloc(sizeof(struct Vnode) * v_num);
    for (int i = 0; i < v_num; i++) {
        g->G[i].FirstEdge.Next = NULL;
    }

    for (int i = 0; i < e_num; i++) {
        scanf("%d %d %d\n", &v, &w, &time);
        insertEdge(g, v, w, time);
    }

    return g;
}

int main(void)
{
    int v_num, e_num;
    scanf("%d %d\n", &v_num, &e_num);

    struct Graph *g = create_graph(v_num, e_num);

    int res = TopSort(g);
    if (res < 0) {
        printf("Impossible\n");
        return 0;
    }

    printf("%d\n", res);
    return 0;
}