#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct edge {
    int vertex;
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

int insertEdge(struct Graph *g, int v, int w)
{
    struct edge *v_edge, *cur;

    v_edge = malloc(sizeof(struct edge));
    v_edge->vertex = w;

    for (cur = &(g->G[v].FirstEdge); cur; cur = cur->Next) {
        if ((!cur->Next) || (cur->Next->vertex > w)) {
            // insert
            v_edge->Next = cur->Next;
            cur->Next = v_edge;
            break;
        }
    }

    return 0;
}

struct Graph *create_graph(int v_num, int e_num)
{
    int v, w;
    struct Graph *g = malloc(sizeof(struct Graph));

    g->Nv = v_num;
    g->Ne = e_num;
    g->G = malloc(sizeof(struct Vnode) * (v_num + 1));
    for (int i = 1; i <= v_num; i++) {
        g->G[i].FirstEdge.Next = NULL;
    }

    for (int i = 0; i < e_num; i++) {
        scanf("%d %d\n", &v, &w);
        insertEdge(g, v, w);
        insertEdge(g, w, v);
    }

    return g;
}

#define QUEUE_SIZE 1001
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

void queue_free(struct queue *q)
{
    free(q);
}

bool isEmpty(struct queue *q)
{
    return q->rear == q->front;
}

bool isFull(struct queue *q)
{
    return q->rear == (q->front - 1);
}

int queue_size(struct queue *q)
{
    if (q->front > q->rear)
        return q->rear + QUEUE_SIZE - q->front;

    return q->rear - q->front;
}

int enqueue(struct queue *q, int v)
{
    if (isFull(q)) {
        return -1;
    }

    q->queue[q->rear] = v;
    q->rear = (q->rear + 1) % QUEUE_SIZE;
    return 0;
}

int dequeue(struct queue *q)
{
    int v;

    if (isFull(q)) {
        return -1;
    }

    v = q->queue[q->front];
    q->front = (q->front + 1) % QUEUE_SIZE;
    return v;
}

int BFS(struct Graph *g, int v)
{
    bool *visited = malloc(sizeof(bool) * (g->Nv + 1));

    for (int i = 1; i <= g->Nv; i++) {
        visited[i] = false;
    }

    struct queue *q = queue_create();
    enqueue(q, v);
    visited[v] = true;

    int level = 0, count = 1;

    while (!isEmpty(q)) {
        int n = queue_size(q);
        // printf("n = %d\n", n);
        for (int i = 0; i < n; i++) {
            v = dequeue(q);
            for (struct edge *e = g->G[v].FirstEdge.Next; e; e = e->Next) {
                if (!visited[e->vertex]) {
                    visited[e->vertex] = true;
                    enqueue(q, e->vertex);
                    count++;
                }
            }
        }

        level++;
        if (level == 6)
            break;
    }

    queue_free(q);
    return count;
}

int six_degree_separation(struct Graph *g)
{
    int count;

    for (int v = 1; v <= g->Nv; v++) {
        count = BFS(g, v);
        printf("%d: %.2f%%\n", v, (float)count * 100 / g->Nv);
    }

    return 0;
}

int main(void)
{
    int v_num, e_num;
    scanf("%d %d\n", &v_num, &e_num);

    struct Graph *g = create_graph(v_num, e_num);
    six_degree_separation(g);

    return 0;
}
