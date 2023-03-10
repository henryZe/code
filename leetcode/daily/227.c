#include <ctype.h>

// #define debug printf
#define debug(...)

#define MAXLEN (3 * 100000)

int operator(char oper, int num, int *stack, int cur)
{
    if (oper == '+') {
        stack[cur++] = num;

    } else if (oper == '-') {
        stack[cur++] = -num;

    } else if (oper == '*') {
        stack[cur - 1] *= num;

    } else if (oper == '/') {
        stack[cur - 1] /= num;
    }

    return cur;
}

int calculate(char * s)
{
    int i;
    int len = strlen(s);
    int stack[MAXLEN];
    int cur = 0;
    int num = 0;
    char preSign = '+';

    for (i = 0; i < len; i++) {
        if (isdigit(s[i])) {
            num *= 10;
            num += s[i] - '0';

        } else if (s[i] == ' ') {
            continue;

        } else {
            cur = operator(preSign, num, stack, cur);
            preSign = s[i];
            num = 0;
        }
    }
    cur = operator(preSign, num, stack, cur);

    num = 0;
    for (i = 0; i < cur; i++) {
        debug("num %d stack %d\n", num, stack[i]);
        num += stack[i];
    }

    return num;
}
