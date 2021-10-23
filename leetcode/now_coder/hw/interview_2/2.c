#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define isM 0
#define isG 1
#define isT 2
#define isNUM 3

int capacity[101][3];

int isUnit(char c)
{
    if (c == 'M')
        return isM;
    if (c == 'G')
        return isG;
    if (c == 'T')
        return isT;

    return isNUM;
}

void str_to_cap(char *str, int *cap)
{
    cap[0] = 0;
    cap[1] = 0;
    cap[2] = 0;

    int n = strlen(str);
    char temp[101];
    strcpy(temp, str);

    char *start = temp;
    for (int i = 0; i < n; i++) {

        int unit = isUnit(temp[i]);
        if (unit < isNUM) {
            temp[i] = 0;
            cap[unit] += atoi(start);
            start = temp + i + 1;
        }
    }

    for (int i = isM; i < isT; i++) {
        while (cap[i] >= 1024) {
            cap[i] -= 1024;
            cap[i+1] += 1;
        }
    }

    // printf("M: %d G: %d T: %d\n", cap[isM], cap[isG], cap[isT]);
}

int compare(const void *a, const void *b)
{
    int a1 = *(int *)a;
    int a2 = *(int *)b;

    if (capacity[a1][isT] != capacity[a2][isT])
        return capacity[a1][isT] - capacity[a2][isT];
    
    if (capacity[a1][isG] != capacity[a2][isG])
        return capacity[a1][isG] - capacity[a2][isG];

    return capacity[a1][isM] - capacity[a2][isM];
}

int main(void)
{
    int num;
    scanf("%d\n", &num);

    char *str[101];
    int idx[101];

    for (int i = 0; i < num; i++) {
        str[i] = (char *)malloc(101);
        scanf("%s\n", str[i]);
        str_to_cap(str[i], capacity[i]);

        idx[i] = i;
    }

    qsort(idx, num, sizeof(int), compare);

    for (int i = 0; i < num; i++) {
        int x = idx[i];
        printf("%s\n", str[x]);
    }

    return 0;
}