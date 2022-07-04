#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vos_int_hash.h"
#include "vos_set.h"
#include "vos_priorityqueue.h"

int QueryDb(int cacheSize, int *ids, int num)
{
    int *next_dist = (int *)malloc(sizeof(int) * num);
    VosHash *hash = VOS_IntHashCreate(1000);
    VosHashIterator hash_it;

    for (int i = num - 1; i >= 0; i --) {
        hash_it = VOS_IntHashFind(hash, ids[i]);
        if (hash_it == VOS_HashIterEnd(hash)) {
            next_dist[i] = num;
        } else {
            next_dist[i] = VOS_HashIterValue(hash, hash_it);
        }
        VOS_HashPut(hash, ids[i], (uintptr_t)i);
    }
    VOS_HashDestroy(hash);

    bool *cache_dist = (bool *)malloc(sizeof(bool) * num);
    int cache_cur = 0;

    for (int i = 0; i < num; i++) {
        cache_dist[i] = false;
    }

    int count = 0;
    int miss_dist;
    VosPriQue *heapq = VOS_PriQueCreate(NULL, NULL);

    for (int i = 0; i < num; i++) {
        if (!cache_dist[i]) {
            // miss
            if (cache_cur == cacheSize) {
                // cache busy
                miss_dist = VOS_PriQueTop(heapq);
                VOS_PriQuePop(heapq);
                if (miss_dist == num) {
                    // no longer appeared
                } else {
                    cache_dist[miss_dist] = false;
                }

            } else {
                // cache free
                cache_cur++;
            }
            count++;
        } else {
            // already cached
        }

        // update cache status
        cache_dist[next_dist[i]] = true;
        VOS_PriQuePush(heapq, next_dist[i]);
    }

    VOS_PriQueDestroy(heapq);

    return count;
}

/* 代码仅供参考，注意避免圈复杂度过大 */
int main(void)
{
    int num;
    if (scanf("%d", &num) != 1) { return -1; }

    int cacheSize;
    if (scanf("%d", &cacheSize) != 1) { return -1; }

    int *ids = malloc(sizeof(int) * num);
    for (int i = 0; i < num; i++) {
        if (scanf("%d", &ids[i]) != 1) {
            return -1;
        }
    }

    int ret = QueryDb(cacheSize, ids, num);
    (void)printf("%d\n", ret);
    return 0;
}
