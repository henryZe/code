#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    return *(int *)a > *(int *)b ? 1 : -1;
}

int main(void)
{
    int a, prev = 0, i;
    int num;
    int array[1000];

    while (scanf("%d", &num) != EOF) {
        for (i = 0; i < num; i++) {
            scanf("%d", &a);
            array[i] = a;
        }
        qsort(array, num, sizeof(int), compare);

        prev = 0;
        for (i = 0; i < num; i++) {
            a = array[i];
            if (a != prev)
                printf("%d\n", a);

            prev = a;
        }
    }
}
