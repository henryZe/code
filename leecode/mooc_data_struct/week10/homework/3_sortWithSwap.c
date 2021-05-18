#include <stdlib.h>
#include <stdio.h>

int *array = NULL;

int compare(const void *a, const void *b)
{
    return array[*(int *)a] - array[*(int *)b];
}

int main(void)
{
    int num;
    scanf("%d\n", &num);

    array = malloc(sizeof(int) * num);
    int *index = malloc(sizeof(int) * num);

    for (int i = 0; i < num; i++) {
        scanf("%d", array + i);
        index[i] = i;
    }

    qsort(index, num, sizeof(int), compare);

    int swap = 0, n, cur, next;

    for (int i = 0; i < num; i++) {
        cur = i;

        if (index[cur] == cur)
            continue;

        if (cur == 0)
            n = -1;
        else
            n = 1;

        while (index[cur] != cur) {
            n++;
            next = index[cur];
            index[cur] = cur;
            cur = next;
        }

        swap += n;
    }

    printf("%d\n", swap);
    return 0;
}
