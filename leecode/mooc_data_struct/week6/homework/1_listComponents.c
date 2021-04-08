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
    g->G = malloc(sizeof(struct Vnode) * v_num);
    for (int i = 0; i < v_num; i++) {
        g->G[i].FirstEdge.Next = NULL;
    }

    for (int i = 0; i < e_num; i++) {
        scanf("%d %d\n", &v, &w);
        insertEdge(g, v, w);
        insertEdge(g, w, v);
    }

    return g;
}

void DFS(struct Graph *g, bool *visited, int v)
{
    int w;

    printf("%d ", v);
    visited[v] = true;

    for (struct edge *e = g->G[v].FirstEdge.Next; e; e = e->Next) {
        w = e->vertex;
        if (!visited[w])
            DFS(g, visited, w);
    }
}

#define QUEUE_SIZE 20
struct queue {
    int queue[QUEUE_SIZE];
    int front;
    int rear;
};

struct queue *queue_create(int num)
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

void BFS(struct Graph *g, bool *visited, int v)
{
    int w;
    struct queue *q = queue_create(g->Nv);

    printf("%d ", v);
    visited[v] = true;
    enqueue(q, v);

    while (!isEmpty(q)) {
        v = dequeue(q);

        for (struct edge *e = g->G[v].FirstEdge.Next; e; e = e->Next) {
            w = e->vertex;
            if (!visited[w]) {
                printf("%d ", w);
                visited[w] = true;
                enqueue(q, w);
            }
        }
    }

    queue_free(q);
}

void ListComponents(struct Graph *g, void (*search)(struct Graph *g, bool *visited, int v))
{
    bool *visited = malloc(sizeof(bool) * g->Nv);
    for (int i = 0; i < g->Nv; i++) {
        visited[i] = false;
    }

    for (int v = 0; v < g->Nv; v++) {
        if (!visited[v]) {
            printf("{ ");
            search(g, visited, v);
            printf("}\n");
        }
    }
}

int main(void)
{
    int v, e;
    scanf("%d %d\n", &v, &e);

    struct Graph *g = create_graph(v, e);

    ListComponents(g, DFS);
    ListComponents(g, BFS);

    return 0;
}
