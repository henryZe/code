#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(void)
{
    char str[100];
    char temp[100];

    scanf("%s\n", str);

    int n = strlen(str);
    for (int i = 0; i < n; i++) {
        temp[i] = str[n - i - 1];
    }
    temp[n] = 0;

    printf("%s\n", temp);
    return 0;
}