#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DIAMETER 15
#define QUEUE_SIZE 100

struct point {
    int x;
    int y;
};

struct queue {
    int queue[QUEUE_SIZE];
    int front;
    int rear;
};

int dis(const struct point *v, const struct point *w)
{
    int x = v->x - w->x;
    int y = v->y - w->y;
    return x * x + y * y;
}

bool isSafe(struct point *point, int v, int distance)
{
    int x = point[v].x;
    int y = point[v].y;
    struct point side[] = {
        [0] = {
            .x = x,
            .y = 50,
        },
        [1] = {
            .x = x,
            .y = -50, 
        },
        [2] = {
            .x = 50,
            .y = y, 
        },
        [3] = {
            .x = -50,
            .y = y, 
        },
    };

    for (int i = 0; i < 4; i++) {
        if (distance * distance >= dis(&side[i], &point[v]))
            return true;
    }
    
    return false;
}

bool Jump(struct point *point, int v, int w, int distance)
{
    if (distance * distance >= dis(&point[v], &point[w]))
        return true;
    return false;
}

bool FirstJump(struct point *point, int v, int distance)
{
    struct point source = { .x = 0, .y = 0 };

    if ((distance + DIAMETER / 2) * (distance + DIAMETER / 2) >= dis(&source, &point[v]))
        return true;
    return false;
}

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

int queue_size(struct queue *q)
{
    return q->rear >= q->front ?
           q->rear - q->front : q->rear + QUEUE_SIZE - q->front;
}

static struct point *crocodile = NULL;

int compare(const void *a, const void *b)
{
    struct point source = { .x = 0, .y = 0 };

    return dis(&crocodile[*(int *)a], &source) - dis(&crocodile[*(int *)b], &source);
}

int Unweighted(struct point *point, int num, int distance, int *dist, int *path)
{
    struct queue *Q = queue_create();

    // init dist & path
    for (int i = 0; i < num; i++) {
        dist[i] = -1;
        path[i] = -1;
    }

    for (int w = 0; w < num; w++) {
        // could be reach in first step
        if (FirstJump(point, w, distance)) {
            dist[w] = 1;
            // circle self
            path[w] = w;
            Enqueue(Q, w);
        }
    }

    qsort(Q->queue, queue_size(Q), sizeof(int), compare);

    while (!IsEmpty(Q)) {
        int v = Dequeue(Q);

        // could reach destination
        if (isSafe(point, v, distance))
            return v;

        for (int w = 0; w < num; w++) {
            if (dist[w] < 0 && Jump(point, v, w, distance)) {
                dist[w] = dist[v] + 1;
                path[w] = v;
                Enqueue(Q, w);
            }
        }
    }

    return -1;
}

void display_path(struct point *point, int i, int *path)
{
    // already return to begin point
    if (path[i] == i) {
        printf("%d %d\n", point[i].x, point[i].y);
        return;
    }

    display_path(point, path[i], path);
    printf("%d %d\n", point[i].x, point[i].y);
}

int main(void)
{
    int num, distance;
    scanf("%d %d\n", &num, &distance);

    int x, y;
    crocodile = malloc(sizeof(struct point) * num);

    for (int i = 0; i < num; i++) {
        scanf("%d %d\n", &x, &y);
        crocodile[i].x = x;
        crocodile[i].y = y;
    }

    struct point source[4] = {
        [0] = {
            .x = DIAMETER,
            .y = 0,
        },
        [1] = {
            .x = -DIAMETER,
            .y = 0,
        },
        [2] = {
            .x = 0,
            .y = DIAMETER,
        },
        [3] = {
            .x = 0,
            .y = -DIAMETER,
        },
    };

    for (int i = 0; i < 4; i++) {
        // could be finished in first step
        if (isSafe(source, i, distance)) {
            printf("1\n");
            return 0;
        }
    }

    int *dist = malloc(sizeof(int) * num);
    int *path = malloc(sizeof(int) * num);

    int res = Unweighted(crocodile, num, distance, dist, path);
    if (res < 0) {
        // impossible to escape
        printf("0\n");
        return 0;
    }

    printf("%d\n", dist[res] + 1);
    display_path(crocodile, res, path);

    return 0;
}
