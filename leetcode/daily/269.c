#include <math.h>
#include <stdbool.h>

// #define debug printf
#define debug(...)

enum {
    NOT_EXIST,
    NOT_VISIT,
    VISITING,
    VISITED,
};

int out[26][26];

int dfs(char *res, int len, int *in_num, int *out_num, int *visited, int v)
{
    int i;

    if (visited[v] == VISITED)
        return len;

    res[len++] = v + 'a';
    visited[v] = VISITING;

    debug("enter %c res %s out_num %d\n",
            v + 'a', res, out_num[v]);

    for (i = 0; i < out_num[v]; i++) {
        int w = out[v][i];

        if (visited[w] == VISITING) {
            debug("loop: %c\n", w + 'a');
            // there is loop in graph
            return -1;
        }

        if (visited[w] == NOT_VISIT) {
            debug("w %d in_num %d\n", w, in_num[w]);
            in_num[w]--;

            if (in_num[w] == 0) {
                len = dfs(res, len, in_num, out_num, visited, w);
                if (len < 0)
                    return -1;
            }
        }
    }

    debug("%c visited\n", v + 'a');
    visited[v] = VISITED;
    return len;
}

char * alienOrder(char ** words, int wordsSize)
{
    int i, j;
    int in_num[26] = {};
    int out_num[26] = {};
    int visited[26] = {};

    char *res = malloc(27);
    memset(res, 0, 27);

    // deal with special case
    if (wordsSize == 1) {
        for (i = 0; i < strlen(words[0]); i++) {
            int v = words[0][i] - 'a';
            visited[v] = NOT_VISIT;
        }
    }

    for (i = 1; i < wordsSize; i++) {
        char *s = words[i - 1];
        char *t = words[i];

        int slen = strlen(s);
        int tlen = strlen(t);
        int len = fmin(slen, tlen);
        bool same = true;

        for (j = 0; j < len; j++) {
            int v = s[j] - 'a';
            int w = t[j] - 'a';

            if (v == w) {
                visited[v] = NOT_VISIT;
                continue;
            }

            int idx = out_num[v]++;

            out[v][idx] = w;
            in_num[w]++;
            same = false;

            visited[v] = NOT_VISIT;
            visited[w] = NOT_VISIT;

            debug("visit: %c %c\n", s[j], t[j]);
            break;
        }

        if (same && slen > tlen) {
            debug("length assert: %s %s\n", s, t);
            return res;
        }

        int residue;

        residue = j;
        while (residue < slen) {
            int v = s[residue++] - 'a';
            visited[v] = NOT_VISIT;
        }

        residue = j;
        while (residue < tlen) {
            int v = t[residue++] - 'a';
            visited[v] = NOT_VISIT;
        }
    }

    int len = 0;

    for (i = 0; i < 26; i++) {
        if (visited[i] == NOT_EXIST)
            continue;

        if (in_num[i] != 0)
            continue;

        len = dfs(res, len, in_num, out_num, visited, i);
        if (len < 0) {
            res[0] = 0;
            break;
        }
    }

    for (i = 0; i < 26; i++) {
        if (visited[i] == NOT_VISIT) {
            // check whether there is in_num[i] still greater than 0
            // if so, there is loop in graph
            res[0] = 0;
            return res;
        }
    }

    debug("res %s\n", res);
    return res;
}
