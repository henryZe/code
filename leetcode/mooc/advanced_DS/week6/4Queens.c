#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool check_dup(int *ret, int pos, int val)
{
    for (int j = 0; j < pos; j++) {
        if (val == ret[j]) {
            return false;
        }
    }
    return true;
}

bool check_diagonal(int *ret, int pos, int val)
{
    for (int j = 0; j < pos; j++) {
        int del_val = ret[j] - val;
        int del_idx = j - pos;

        if ((del_val == del_idx) || (del_val == -del_idx))
            return false;
    }
    return true;
}

bool queens(int *ret, int num, int pos)
{
    if (num == pos)
        return true;

    for (int i = 1; i <= num; i++) {
        if (check_dup(ret, pos, i) == false)
            continue;
        if (check_diagonal(ret, pos, i) == false)
            continue;
        
        ret[pos] = i;
        if (queens(ret, num, pos + 1) == true)
            return true;
        // backtrack here!
    }

    return false;
}

int main(void)
{
    int size = 4;
    int *ret = malloc(sizeof(int) * size);

    if (queens(ret, size, 0) == false)
        return -1;

    for (int i = 0; i < size; i++) {
        printf("%d,", ret[i]);
    }
    printf("\n");
    return 0;
}
