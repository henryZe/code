#include <stdio.h>
#include <string.h>

int remove_dup(char *str)
{
    int pos = 0;
    char temp[100] = {0};

    for (int i = 0; i < strlen(str); i++) {
        char token[] = {str[i], 0};

        if (strstr(temp, token) == NULL) {
            pos = strlen(temp);
            temp[pos] = str[i];
            temp[++pos] = 0;
        }
    }

    printf("%s\n", temp);
    return 0;
}

int main(void)
{
    char str[100] = {0};

    while (scanf("%s\n", str) != EOF) {
        remove_dup(str);
    }
    return 0;
}
