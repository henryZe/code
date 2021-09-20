#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int hash[11111112] = {0};

int main(void)
{
    int num;
    scanf("%d\n", &num);

    int index, value;
    for (int i = 0; i < num; i++) {
        scanf("%d %d\n", &index, &value);
        hash[index] += value;
    }

    for (int i = 0; i < 11111112; i++) {
        if (hash[i])
            printf("%d %d\n", i, hash[i]);
    }

    return 0;
}