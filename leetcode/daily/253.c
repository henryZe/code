#include <stdlib.h>

struct event {
    int time;
    int booked;
};

int compare(const void *a, const void *b)
{
    struct event *arg1 = (struct event *)a;
    struct event *arg2 = (struct event *)b;

    if (arg1->time == arg2->time)
        return arg1->booked - arg2->booked;

    return arg1->time - arg2->time;
}

int minMeetingRooms(int** intervals, int intervalsSize, int* intervalsColSize)
{
    int i;
    struct event *diff = malloc(sizeof(struct event) * intervalsSize * 2);

    // O(N)
    for (i = 0; i < intervalsSize; i++) {
        diff[2 * i].time = intervals[i][0];
        diff[2 * i].booked = 1;

        diff[2 * i + 1].time = intervals[i][1];
        diff[2 * i + 1].booked = -1;
    }

    // O(N * logN)
    qsort(diff, intervalsSize * 2, sizeof(struct event), compare);

    int cur = 0, res = 0;
    for (i = 0; i < intervalsSize * 2; i++) {
        cur += diff[i].booked;
        if (cur > res)
            res = cur;
    }

    return res;
}
