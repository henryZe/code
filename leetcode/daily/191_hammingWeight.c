#include <stdio.h>
#include <stdint.h>

uint32_t lowbit(uint32_t x)
{
    return x & (-x);
}

int hammingWeight(uint32_t n)
{
    int i = 0;

    while (n) {
        n -= lowbit(n);
        i++;
    }

    return i;
}

int main(void)
{
    printf("%d\n", hammingWeight(0b11111111111111111111111111111101));
    return 0;
}
