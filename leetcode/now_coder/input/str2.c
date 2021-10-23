#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b)
{
    return strcmp(*(char **)a, *(char **)b);
}

int main(void)
{
    char *str_p[100];
    for (int i = 0; i < 100; i++) {
        str_p[i] = (char *)malloc(100);
    }

    int num = 0;
    while (scanf("%s", str_p[num]) != EOF) {
        // printf("test %s\n", str_p[num]);
        num++;
        char c = getchar();
        if (c == '\n' || c == EOF) {
            qsort(str_p, num, sizeof(char *), compare);
            int i = 0;
            for (i = 0; i < num - 1; i++) {
                printf("%s ", str_p[i]);
            }
            if (i == num - 1) {
                printf("%s\n", str_p[i]);
            }
            // printf("test %d\n", i);
            num = 0;
        }
    }

    return 0;
}