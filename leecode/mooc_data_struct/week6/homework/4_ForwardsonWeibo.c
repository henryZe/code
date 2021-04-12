// https://pintia.cn/problem-sets/994805342720868352/problems/994805392092020736

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

struct Graph *create_graph(int v_num)
{
    int v, e_num;
    struct Graph *g = malloc(sizeof(struct Graph));

    g->Nv = v_num;
    g->G = malloc(sizeof(struct Vnode) * (v_num + 1));
    for (int i = 1; i <= v_num; i++) {
        g->G[i].FirstEdge.Next = NULL;
    }

    for (int w = 1; w <= v_num; w++) {
        scanf("%d ", &e_num);
        for (int j = 0; j < e_num; j++) {
            scanf("%d ", &v);
            insertEdge(g, v, w);
        }
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

int BFS(struct Graph *g, int v, int level)
{
    bool *visited = malloc(sizeof(bool) * (g->Nv + 1));

    for (int i = 1; i <= g->Nv; i++) {
        visited[i] = false;
    }

    struct queue *q = queue_create();
    enqueue(q, v);
    visited[v] = true;

    int cur = 0, count = 0;

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

        cur++;
        if (level == cur)
            break;
    }

    queue_free(q);
    return count;
}

int level_degree_separation(struct Graph *g, int v, int level)
{
    printf("%d\n", BFS(g, v, level));
    return 0;
}

int main(void)
{
    int v_num, level;
    scanf("%d %d\n", &v_num, &level);

    struct Graph *g = create_graph(v_num);

    int check_v_num, v;
    scanf("%d ", &check_v_num);

    for (int i = 0; i < check_v_num; i++) {
        scanf("%d ", &v);
        level_degree_separation(g, v, level);
    }

    return 0;
}

