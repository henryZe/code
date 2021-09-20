#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int compare(const void *a, const void *b)
{
    return strcmp(*(char **)a, *(char **)b);
}

int main(void)
{
    int num;
    scanf("%d\n", &num);

    char *arr[num];

    for (int i = 0; i < num; i++) {
        arr[i] = (char *)malloc(100);
        scanf("%s\n", arr[i]);
    }
    qsort(arr, num, sizeof(char *), compare);

    for (int i = 0; i < num; i++) {
        printf("%s\n", arr[i]);
    }
    return 0;
}