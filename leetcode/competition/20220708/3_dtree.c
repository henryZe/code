#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define idx(x) (x - 'a')
#define LETTER_RANGE 26
#define ALLOW_DIFF 1

struct tree_n {
    bool end;
    struct tree_n *nodes[LETTER_RANGE];
};

void init_tree_node(struct tree_n *n, bool end)
{
    n->end = end;
    for (int i = 0; i < LETTER_RANGE; i++)
        n->nodes[i] = NULL;
}

struct tree_n *grow_tree(struct tree_n *root, char c, bool end)
{
    struct tree_n *n;

    if (!root->nodes[idx(c)]) {
        // not exist
        n = (struct tree_n *)malloc(sizeof(struct tree_n));
        init_tree_node(n, end);

        root->nodes[idx(c)] = n;
        return n;
    }

    // already exist
    if (end)
        // if the word ends, mark it
        root->nodes[idx(c)]->end = true;

    return root->nodes[idx(c)];
}

struct tree_n *gen_dict_tree(char **dict, int dictionarySize)
{
    struct tree_n *start = (struct tree_n *)malloc(sizeof(struct tree_n));
    init_tree_node(start, false);

    for (int i = 0; i < dictionarySize; i++) {

        struct tree_n *n = start;
        int len = strlen(dict[i]);

        for (int j = 0; j < (len - 1); j++) {
            n = grow_tree(n, dict[i][j], false);
        }

        n = grow_tree(n, dict[i][len - 1], true);
    }

    return start;
}

void dfs(struct tree_n *tree, char *word, int len, int i, int diff, int *res)
{
    if (diff > ALLOW_DIFF)
        // already fail to meet
        return;

    if (i == len) {
        // word is over
        // printf("line %d diff %d end %s\n",
        //         __LINE__, diff, tree->end ? "yes" : "no");
        if (diff == ALLOW_DIFF && tree->end) {
            // if meets the conditions, then count it
            (*res)++;
            // printf("res++ %d\n", *res);
        }
        return;
    }

    for (int j = 0; j < LETTER_RANGE; j++) {
        if (tree->nodes[j]) {
            // node exists, then dfs
            if (j != idx(word[i]))
                // not equal current character, diff + 1
                dfs(tree->nodes[j], word, len, i + 1, diff + 1, res);
            else
                // equal current character
                dfs(tree->nodes[j], word, len, i + 1, diff, res);
        }
    }
}

int walk_tree(struct tree_n *tree, char *word)
{
    int res = 0;
    dfs(tree, word, strlen(word), 0, 0, &res);
    return res;
}

int *QueryWords(char **dictionary, int dictionarySize,
                char **words, int wordsSize,
                int *returnSize)
{
    *returnSize = wordsSize;

    int *res = (int *)malloc(sizeof(int) * wordsSize);
    struct tree_n *tree = gen_dict_tree(dictionary, dictionarySize);

    // walk all trees
    for (int i = 0; i < wordsSize; i++) {
        res[i] = walk_tree(tree, words[i]);
        // printf("%s done\n", words[i]);
    }

    return res;
}

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

int main(void)
{
    char *dictionary[] = {"aba", "abb", "abc", "bba", "bbb", "bbc"};
    int dictionarySize = ARRAY_SIZE(dictionary);

    char *words[] = {"abc", "cbc"};
    int wordsSize = ARRAY_SIZE(words);

    int returnSize;
    int *res = QueryWords(dictionary, dictionarySize,
                            words, wordsSize, &returnSize);

    for (int i = 0; i < returnSize; i++)
        printf("%d ", res[i]);
    printf("\n");

    return 0;
}
