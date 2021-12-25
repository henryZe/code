#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct seatInfo {
    int *seat;
    int seatNum;
    int present;
};

// dynamic programming
int searchSeat(struct seatInfo *s)
{
    if (s->present == 0)
        return 0;

    if (s->present == 1)
        return s->seatNum - 1;

    if (s->present == s->seatNum)
        return -1;

    int begin = -1;
    int cur_idx, interval, idx, min_interval = -1;

    for (int i = 0; i < s->seatNum; i++) {
        if (begin == -1 && s->seat[i] == 0) {
            begin = i;
        } else if (s->seat[i] == 1 && begin != -1) {
            cur_idx = (begin + i - 1) / 2;
            interval = cur_idx - begin;
            if (interval > min_interval) {
                idx = cur_idx;
                min_interval = interval;
            }
            begin = -1;
        }
    }

    // last pos is idle
    if (begin != -1) {
        cur_idx = s->seatNum - 1;
        interval = cur_idx - begin;

        if (interval > min_interval) {
            idx = cur_idx;
            min_interval = interval;
        }
    }

    return idx;
}

int main(void)
{
    int num;
    scanf("%d\n", &num);

    int seat[500];
    for (int i = 0; i < num; i++) {
        seat[i] = 0;
    }

    struct seatInfo s;
    s.seat = seat;
    s.seatNum = num;
    s.present = 0;

    int idx;
    getchar();
    while (1) {
        int v;
        scanf("%d", &v);
        // printf("%d\n", v);

        if (v == 1) {
            idx = searchSeat(&s);
            // printf("sit %d\n", idx);
            seat[idx] = 1;
            s.present++;
        } else {
            seat[-v] = 0;
            s.present--;
            // printf("del %d\n", -v);
        }

        if (getchar() != ',') {
            // end
            break;
        }
    }

    printf("%d\n", idx);
    return 0;
}
