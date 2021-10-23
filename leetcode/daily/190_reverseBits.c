#include <stdio.h>

// 分治法
unsigned int reverseBits(unsigned int x)
{
    unsigned int M1 = 0x55555555;
    unsigned int M2 = 0x33333333;
    unsigned int M4 = 0x0F0F0F0F;
    unsigned int M8 = 0x00FF00FF;

    x = ((x >> 1) & M1) | ((x & M1) << 1);
    x = ((x >> 2) & M2) | ((x & M2) << 2);
    x = ((x >> 4) & M4) | ((x & M4) << 4);
    x = ((x >> 8) & M8) | ((x & M8) << 8);

    return (x >> 16) | (x << 16);
}

int main(void)
{
    unsigned int i = 0b00000010100101000001111010011100;
    printf("%d\n", reverseBits(i));

    return 0;
}