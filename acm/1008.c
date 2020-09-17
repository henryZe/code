#include <stdio.h>

int factorial(int n)
{
    if (n != 1)
		return n * factorial(n-1);
    else
        return 1;
}

int main(void)
{
    int N, P;

    scanf("%d %d\n", &N, &P);
    printf("%d\n", factorial(N) % P);

    return 0;
}
