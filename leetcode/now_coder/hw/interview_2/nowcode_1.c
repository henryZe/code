#include <stdio.h>
#include <stdlib.h>

// recursion
int apple(long long num, int time)
{
    while (num % 2 == 0) {
        num /= 2;
        time++;
    }

    if (num == 1)
        return time;

    int t1 = apple(num + 1, time + 1);
    int t2 = apple(num - 1, time + 1);

    return t1 < t2 ? t1 : t2;
}

int main(void)
{
    long long num;

    while (scanf("%lld\n", &num) != EOF) {
        printf("%d\n", apple(num, 0));
    }

    return 0;
}
