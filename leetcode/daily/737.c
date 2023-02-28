#include <stdbool.h>
#include <string.h>
#include <stdio.h>

int find_set(int *parent, int idx)
{
    if (parent[idx] != idx)
        parent[idx] = find_set(parent, parent[idx]);
    return parent[idx];
}

void union_set(int *parent, int *rank, int idx1, int idx2)
{
    int p = find_set(parent, idx1);
    int q = find_set(parent, idx2);

    if (p == q)
        return;

    if (rank[p] == rank[q])
        rank[p]++;
    if (rank[p] > rank[q])
        parent[q] = p;
    else
        parent[p] = q;
}

struct dict {
    int size;
    char dict[2000 * 2][20];
};

int in(struct dict *d, char *word)
{
    int i;

    for (i = 0; i < d->size; i++) {
        if (strcmp(d->dict[i], word) == 0)
            return i;
    }

    return -1;
}

int append(struct dict *d, char *word)
{
    sprintf(d->dict[d->size], "%s", word);
    return d->size++;
}

bool areSentencesSimilarTwo(char ** sentence1, int sentence1Size,
                            char ** sentence2, int sentence2Size,
                            char *** similarPairs, int similarPairsSize,
                            int* similarPairsColSize)
{
    int i, j;

    // 1. complete similarPairs union-find-set
    int *parent = malloc(2000 * 2 * sizeof(int));
    int *rank = malloc(2000 * 2 * sizeof(int));

    for (i = 0; i < (2000 * 2); i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    struct dict *d = malloc(sizeof(struct dict));
    d->size = 0;

    for (i = 0; i < similarPairsSize; i++) {
        int idx1 = in(d, similarPairs[i][0]);
        if (idx1 == -1)
            idx1 = append(d, similarPairs[i][0]);

        int idx2 = in(d, similarPairs[i][1]);
        if (idx2 == -1)
            idx2 = append(d, similarPairs[i][1]);

        union_set(parent, rank, idx1, idx2);
    }

    // 2. check each word in sentence by set
    if (sentence1Size != sentence2Size) {
        // printf("sentence1Size != sentence2Size\n");
        return false;
    }

    for (i = 0; i < sentence1Size; i++) {
        // same words
        if (strcmp(sentence1[i], sentence2[i]) == 0)
            continue;

        int idx1 = in(d, sentence1[i]);
        int idx2 = in(d, sentence2[i]);
        if (idx1 == -1 || idx2 == -1) {
            // printf("%s %d & %s %d not in\n",
            //         sentence1[i], idx1, sentence2[i], idx2);

            // if not in set, no possible similar words
            return false;
        }

        // similar words
        if (find_set(parent, idx1) != find_set(parent, idx2)) {
            // printf("%s %d parent %d & %s %d parent %d not similar\n",
            //         sentence1[i], idx1, find_set(parent, idx1),
            //         sentence2[i], idx2, find_set(parent, idx2));

            return false;
        }
    }

    return true;
}
