#include <stdbool.h>
#include <stdlib.h>

struct event {
    int point;
    int people;
};

int compare(const void *a, const void *b)
{
    struct event *arg1 = (struct event *)a;
    struct event *arg2 = (struct event *)b;

    if (arg1->point == arg2->point)
        return arg1->people - arg2->people;

    return arg1->point - arg2->point;
}

bool carPooling(int** trips, int tripsSize, int* tripsColSize, int capacity){
    int i;
    // 1. initialize event array
    struct event *array = malloc(sizeof(struct event) * tripsSize * 2);

    for (i = 0; i < tripsSize; i++) {
        array[2 * i].people = trips[i][0];
        array[2 * i].point = trips[i][1];

        array[2 * i + 1].people = -(trips[i][0]);
        array[2 * i + 1].point = trips[i][2];
    }

    // 2. sort event array by point
    qsort(array, tripsSize * 2, sizeof(struct event), compare);

    // 3. walk the trip, check pass or not
    for (i = 0; i < tripsSize * 2; i++) {
        capacity -= array[i].people;
        if (capacity < 0) {
            // printf("people %d point %d\n",
            //         array[i].people, array[i].point);
            return false;
        }
    }

    return true;
}
