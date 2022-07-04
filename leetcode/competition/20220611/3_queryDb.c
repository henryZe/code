#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct slot {
    int request_idx;
    int cache_idx;
};

int whether_in(int request, int *array, int cur_num)
{
    for (int i = 0; i < cur_num; i++) {
        if (request == array[i])
            return i;
    }

    return -1;
}

int find_max(struct slot *place, int len)
{
    struct slot tmp = place[0];

    for (int i = 1; i < len; i++) {
        tmp = tmp.request_idx > place[i].request_idx ? tmp : place[i];
    }

    return tmp.cache_idx;
}

int QueryDb(int cacheSize, int *ids, int num)
{
    int *cache = malloc(sizeof(int) * cacheSize);
    int cache_cur = 0;
    struct slot *place = malloc(sizeof(struct slot) * num);
    int place_cur;
    int count = 0;
    int ret, j, index;

    for (int i = 0; i < num; i++) {
        // printf("ids %d\n", ids[i]);

        // not in cache
        if (whether_in(ids[i], cache, cache_cur) < 0) {
            // printf("missed %d %d\n", i, ids[i]);

            // idle place of cache
            if (cache_cur < cacheSize) {
                cache[cache_cur++] = ids[i];

            } else {
                // replace data
                place_cur = 0;
                for (j = 0; j < cacheSize; j++) {
                    ret = whether_in(cache[j], ids + i + 1, num - i - 1);
                    if (ret < 0) {
                        // not appeared in requests any more
                        cache[j] = ids[i];
                        break;
                    } else {
                        // record index of request
                        place[place_cur].request_idx = ret;
                        place[place_cur++].cache_idx = j;
                    }
                }
                if (j == cacheSize) {
                    index = find_max(place, place_cur);
                    // printf("cache[%d] = %d -> %d\n", index, cache[index], ids[i]);
                    cache[index] = ids[i];
                }
            }

            count++;
        } else {
            // printf("cached %d %d\n", i, ids[i]);
        }
    } 

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
