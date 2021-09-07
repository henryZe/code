#include <stdlib.h>
#include <stdio.h>

int compare(const void *a, const void *b)
{
    return *(int *)b - *(int *)a;
}

int findKth(int* a, int aLen, int n, int K )
{
    qsort(a, n, sizeof(int), compare);
    return a[K - 1];
}

void print_array(int* a, int aLen)
{
    printf("array:\n");
    for (int i = 0; i < aLen; i++) {
        printf("%d\n", a[i]);
    }
    printf("\n");
}

int main(void)
{
    int num;
    scanf("%d\n", &num);

    int *array = malloc(num * sizeof(int));
    for (int i = 0; i < num; i++) {
        scanf("%d,", array + i);
    }

    int k;
    scanf("%d\n", &k);

    int ret = findKth(array, num, num, k);
    printf("%d\n", ret);

    // print_array(array, num);

    return 0;
}