#include <stdio.h>

int f(void)
{
    printf("strong func\n");
    return 0;
}

int redundant(void)
{
    printf("redundant func\n");
    return 0;
}
