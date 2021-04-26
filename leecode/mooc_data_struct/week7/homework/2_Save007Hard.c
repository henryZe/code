#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DIAMETER 15

struct point {
    int x;
    int y;
};

int dis(struct point *v, struct point *w)
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

bool dfs(struct point *point, bool *visited, int num, int v, int distance)
{
    bool res;

    printf("v %d (%d, %d)\n", v, point[v].x, point[v].y);

    dist[v] = true;
    if (isSafe(point, v, distance)) {
        return true;
    }

    for (int i = 0; i < num; i++) {
        if (!visited[i] && Jump(point, v, i, distance)) {
            res = dfs(point, visited, num, i, distance);
            if (res)
                return res;
        }
    }

    return false;
}

bool Unweighted(struct point *point, int num, int distance, int *dist, int *path)
{
    bool res;

    for (int i = 0; i < num; i++) {
        dist[i] = -1;
        path[i] = -1;
    }

    for (int w = 0; w < num; w++) {
        if (dist[w] < 0 && FirstJump(point, w, distance)) {
            dist[w] = 1;
            // circle self
            path[w] = w;
            Enqueue(w, Q);
        }
    }

    while (!IsEmpty(Q)) {
        int v = Dequeue(Q);

        if (isSafe(point, v, distance)) {
            return true;
        }

        for (int i = 0; i < num; i++) {

            dist[i] = dist[v] + 1;
            path[v] = ;
            if (isSafe(point, v, distance)) {
                return true;
            }

            if (dist[i] < 0) {
                dist[i] = dist[V] + 1;
                path[i] = V;
                Enqueue(i, Q);
            }
        }
    }


}

int main(void)
{
    int num, distance;
    scanf("%d %d\n", &num, &distance);

    int x, y;
    struct point *crocodile = malloc(sizeof(struct point) * num);

    for (int i = 0; i < num; i++) {
        scanf("%d %d\n", &x, &y);
        crocodile[i].x = x;
        crocodile[i].y = y;
    }

    // add start as 0 and end as num + 1
    int *dist = malloc(sizeof(int) * num);
    int *path = malloc(sizeof(int) * num);

    bool res = Unweighted(crocodile, num, distance, dist, path);
    if (res) {
        printf("\n");
    } else {
        printf("0\n");
    }

    return 0;
}
