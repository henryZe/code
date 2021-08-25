#include <stdio.h>

int bottle(void)
{
    int a, b, c;
    int sum;

    while (scanf("%d", &a) != EOF) {
        sum = 0;
        while (a > 2) {
            b = a / 3;
            c = a % 3;
            a = b + c;
            sum += b;
        }

        if (a == 2)
            sum += 1;

        if (sum)
            printf("%d\n", sum);
    }

    return 0;
}

int main(void)
{
	return bottle();
}
