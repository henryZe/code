#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool cal(char *str, int l, int r)
{
    while (l >= 0 && r < strlen(str)) {
        if (str[l] != str[r])
            return false;
        l -= 1;
        r += 1;
    }

    if (l >= 0)
        return false;

    if (r < strlen(str))
        return false;

    return true;
}

bool judge(char *str)
{
    int n = strlen(str);
    int mid = (n - 1) / 2;

    return cal(str, mid, mid) || cal(str, mid, mid + 1);
}

int main(void)
{
    char *str = "absba";
    printf("%s\n", judge(str) ? "true" : "false");
    return 0;
}
