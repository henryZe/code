#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    struct point arr[] = {
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
        if (distance * distance >= dis(&arr[i], &point[v]))
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

    if ((distance + 15 / 2) * (distance + 15 / 2) >= dis(&source, &point[v]))
        return true;
    return false;
}

bool dfs(struct point *point, bool *visited, int num, int v, int distance)
{
    bool res;

    // printf("path %d\n", v);

    visited[v] = true;
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

bool ListComponents(struct point *point, int num, int distance)
{
    bool res;
    bool *visited = malloc(sizeof(bool) * num);

    for (int i = 0; i < num; i++) {
        visited[i] = false;
    }

    for (int i = 0; i < num; i++) {
        // printf("start\n");
        if (!visited[i] && FirstJump(point, i, distance)) {
            res = dfs(point, visited, num, i, distance);
            if (res)
                return res;
        }
        // printf("end\n");
    }

    return false;
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

    bool res = ListComponents(crocodile, num, distance);
    if (res)
        printf("Yes\n");
    else
        printf("No\n");

    return 0;
}
