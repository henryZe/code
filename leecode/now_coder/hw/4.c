#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int n;
    char str[101];
    char *p;

    while (scanf("%s\n", str) != EOF) {
        p = str;

again:
        n = strlen(p);
        if (n < 8) {
            for (int i = n; i < 8; i++)
                p[i] = '0';
        }
        printf("%.8s\n", p);

        if (n > 8) {
            p += 8;
            goto again;
        }
    }

    return 0;
}
