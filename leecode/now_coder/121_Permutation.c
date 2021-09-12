#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hash {
    int table[256];
    int type;
    int num;
};

void dfs(char **ret, int *retSize, char *cur, int pos, struct hash *h)
{
    if (pos + 1 == h->num) {
        ret[*retSize] = cur;
        (*retSize)++;
        printf("cur %s\n", cur);
        return;
    }

    for (int i = 0; i < h->type; i++) {
        for (int j = 0; j < 256; j++) {
            if (h->table[j]) {
                h->table[j]--;
                char *newStr = (char *)malloc(h->num);
                memcpy(newStr, cur, pos);
                newStr[pos] = j;
                dfs(ret, retSize, newStr, pos + 1, h);
                h->table[j]++;
            }
        }
    }
}

char **Permutation(char *ss)
{
    if (!ss)
        return NULL;

    int n = strlen(ss);
    if (!n)
        return NULL;

    struct hash h;
    memset((char *)&h, 0, sizeof(h));
    h.type = 0;
    h.num = n;

    for (int i = 0; i < n; i++) {
        int index = ss[i];
        if (h.table[index] == 0) {
            h.type++;
        }
        h.table[index]++;
    }

    char **ret = (char **)malloc(n * sizeof(char *));
    ret[0] = NULL;
    int size = 0;
    char *cur = (char *)malloc(n);
    dfs(ret, &size, cur, 0, &h);

    return ret;
}

int main(void)
{
    char **ret = Permutation("ab");
    int i = 0;
    while (ret[i]) {
        printf("%s\n", ret[i]);
        i++;
    }

    return 0;
}
