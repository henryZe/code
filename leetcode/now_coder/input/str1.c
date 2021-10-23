#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b)
{
    return strcmp(*(char **)a, *(char **)b);
}

int main(void)
{
    int num;
    scanf("%d", &num);

    char *str_p[num];
    for (int i = 0; i < num; i++) {
        str_p[i] = (char *)malloc(100);
        scanf("%s", str_p[i]);
    }

    qsort(str_p, num, sizeof(char *), compare);
    int i;
    for (i = 0; i < num - 1; i++) {
        printf("%s ", str_p[i]);
    }
    if (i == num - 1) {
        printf("%s\n", str_p[i]);
    }

    return 0;
}