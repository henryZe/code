#include <stdio.h>
#include <time.h>
#include <math.h>

void my_function(void)
{
    printf("hello world\n");
}

#define MAXN 10

double f1(int n, double a[], double x)
{
    double res = 0;

    for (int i = 1; i < n + 1; i++)
        res += a[i] * pow(x, i);

    return res;
}

double f2(int n, double a[], double x)
{
    double res = a[n];

    for (int i = n; i > 0; i--)
        res = a[i - 1] + res * x;

    return res;
}

int main(void)
{
    clock_t start, stop;
    double duration, res;

    double a[MAXN];
    for (int i = 0; i < MAXN; i++)
        a[i] = (double)i;

    start = clock();
    res = f1(MAXN - 1, a, 1.1);
    printf("res = %f\n", res);
    stop = clock();

    duration = ((double)(stop - start)) / CLOCKS_PER_SEC;
    printf("duration = %f\n", duration);

    start = clock();
    res = f2(MAXN - 1, a, 1.1);
    printf("res = %f\n", res);
    stop = clock();

    duration = ((double)(stop - start)) / CLOCKS_PER_SEC;
    printf("duration = %f\n", duration);

    return 0;
}
