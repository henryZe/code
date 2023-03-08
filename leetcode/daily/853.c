#include <stdlib.h>

// #define debug printf
#define debug(...)

int *p;

int compare(const void *a, const void *b)
{
    int a1 = *(int *)a;
    int a2 = *(int *)b;

    return p[a2] - p[a1];
}

int carFleet(int target, int* position, int positionSize,
             int* speed, int speedSize)
{
    int i;
    int idx[positionSize];

    for (i = 0; i < positionSize; i++) {
        idx[i] = i;
    }

    p = position;
    qsort(idx, positionSize, sizeof(int), compare);

    float time[positionSize];
    int index;

    for (i = 0; i < positionSize; i++) {
        index = idx[i];
        time[i] = (float)(target - position[index]) / speed[index];
        debug("time %f pos %d speed %d\n",
                time[i], target - position[index], speed[index]);
    }

    int cur_len = 0;
    int res = 0;

    while ((positionSize - cur_len) > 1) {
        float lead = time[cur_len];

        debug("lead %f next %f\n", lead, time[cur_len + 1]);

        if (time[cur_len + 1] > lead) {
            res++;
        } else {
            time[cur_len + 1] = lead;
        }

        cur_len++;
    }

    return res + (positionSize - cur_len);
}
