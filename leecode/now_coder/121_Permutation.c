#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hash {
    int table[256];
    char *hash;
    int type;
    int num;
};

void dfs(char **ret, int *retSize, char *cur, int pos, struct hash *h)
{
    if (pos == h->num) {
        ret[*retSize] = cur;
        (*retSize)++;
        return;
    }

    for (int i = 0; i < h->type; i++) {
        int j = h->hash[i];
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
    h.hash = (char *)malloc(n);

    for (int i = 0; i < n; i++) {
        int index = ss[i];
        if (h.table[index] == 0) {
            h.hash[h.type] = index;
            h.type++;
            h.hash[h.type] = 0;
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
    int i = 0;
    // char **ret = Permutation("ab");
    char **ret = Permutation("abc");
    while (ret[i]) {
        printf("%s\n", ret[i]);
        i++;
    }
    return 0;
}
