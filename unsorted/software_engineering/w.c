#include <stdio.h>

int __attribute__((weak)) f(void)
{
    printf("weak func\n");
    return 0;
}

int __attribute__((weak)) g(void)
{
    printf("weak func\n");
    return 0;
}