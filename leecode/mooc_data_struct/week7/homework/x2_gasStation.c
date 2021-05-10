#include <stdio.h>
#include <math.h>

void Dijkstra(int s, int service)
{
    while (1) {
        V = 未收录顶点中，dist最小者;
        if (V 不存在)
            break;

        collected[V] = true;
        for (V 的每个邻接点 W) {
            if (collected[W] == false) {
                if (dist[V] + E<V, W> < dist[W]) {
                    // initialize dist[] as infinite & path[] as -1
                    dist[W] = dist[V] + E<V, W>;
                    path[W] = V;
                }
            }
        }
    }
}




int main(void)
{
    int n_house, n_candidate, n_road, d_range;
    scanf("%d %d %d %d\n", &n_house, &n_candidate, &n_road, &d_range);

    // matrix
    struct graph *g = create_graph(n_house + n_candidate, n_road);

    int dist = malloc(sizeof(int) * (n_house + n_candidate));
    for (int i = 0; i < n_candidate; i++) {
        min_dist = Dijkstra(n_house + i, dist, d_range);
        if (min_dist < 0)
            continue;

        if (min_dist > cur_min) {
            cur_min = min_dist;
            cur = i;

        } else if (min_dist == cur_min) {
            if (avg(dist) > cur_avg) {
                cur_avg = avg(dist);
                cur = i;
            }
        }
    }

    if (!cur) {
        printf("No Solution\n");
        return 0;
    }

    printf("G%d\n", cur + 1);
    printf("%.1f %.1f", sqrt(cur_min), cur_avg);
    return 0;
}