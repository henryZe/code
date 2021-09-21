#include <stdio.h>
#include <stdlib.h>

int apple(long long num, int time)
{
    if (num == 1)
        return 0;

    while (num != 1) {
        if (num % 2 == 0) {
            num /= 2;
            time++;
        } else {
            int t1 = apple(num + 1, time + 1);
            int t2 = apple(num - 1, time + 1);
            time = t1 < t2 ? t1 : t2;
            break;
        }
    }

    return time;
}

int main(void)
{
    long long num;

    while (scanf("%lld\n", &num) != EOF) {
        printf("%d\n", apple(num, 0));
    }

    return 0;
}
