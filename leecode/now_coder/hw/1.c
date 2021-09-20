#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[5000];
    while (scanf("%s", str) != EOF);

    printf("%ld\n", strlen(str));
    return 0;
}
