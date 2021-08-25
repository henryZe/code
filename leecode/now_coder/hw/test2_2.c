#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct error {
    char file[32];
    int line;
    int freq;
};

struct error array[4096];

int compare(const void *a, const void *b)
{
    return ((struct error *)b)->freq - ((struct error *)a)->freq;
}

int main(void)
{
    char file[4096];
    char *ret, *p;
    int line;
    int num = 0;

    while (scanf("%s %d\n", file, &line) != EOF) {
        p = file;
        while (1) {
            ret = strstr(p, "\\");
            if (!ret)
                break;

            p = ret + 1;
        }

        int i;
        for (i = 0; i < num; i++) {
            if (array[i].line == line) {
                if (strcmp(p, array[i].file) == 0) {
                    array[i].freq++;
                    break;
                }
            }
        }
        if (i == num) {
            strcpy(array[i].file, p);
            array[i].line = line;
            array[i].freq = 1;
            num++;

            // printf("%s %d %d\n", array[i].file, array[i].line, array[i].freq);
        }
    }

    qsort(array, num, sizeof(struct error), compare);

    char str[17] = {0};
    for (int i = 0; i < 8 && i < num; i++) {
        int len = strlen(array[i].file);
        if (len > 16) {
            strcpy(str, array[i].file + len - 16);
            printf("%s %d %d\n", str, array[i].line, array[i].freq);
        } else {
            printf("%s %d %d\n", array[i].file, array[i].line, array[i].freq);
        }
    }

    return 0;
}