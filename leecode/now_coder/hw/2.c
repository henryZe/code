#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[501];
    char c[5];
    scanf("%[^\n]", str);
    getchar();
    scanf("%s\n", c);
    int t = 0;
    char *p = str;
    while (1) {
        p = strstr(p, c);
        if (p == NULL)
            break;
        p++;
        t++;
    }

    if (c[0] >= 'a' && c[0] <= 'z') {
        // a
        c[0] = c[0] + 'A' - 'a';

    } else if (c[0] >= 'A' && c[0] <= 'Z') {
        // A
        c[0] = c[0] + 'a' - 'A';

    } else {
        // number
        goto end;
    }

    p = str;
    while (1) {
        p = strstr(p, c);
        if (p == NULL)
            break;
        p++;
        t++;
    }

end:
    printf("%d\n", t);
    return 0;
}
