#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define idx(x) (x - 'a')

struct tree_n {
    bool end;
    char c;
    struct tree_n *nodes[26];
};

void init_tree_node(struct tree_n *n, bool end)
{
    n->end = end;
    for (int i = 0; i < 26; i++)
        n->nodes[i] = NULL;
}

struct tree_n *grow_tree(struct tree_n *root, char c, bool end)
{
    struct tree_n *n;

    if (!root->nodes[idx(c)]) {
        n = (struct tree_n *)malloc(sizeof(struct tree_n));
        init_tree_node(n, end);

        root->nodes[idx(c)] = n;
    }

    if (end)
        init_tree_node(root->nodes[idx(c)], end);
    else
        init_tree_node(root->nodes[idx(c)], root->nodes[idx(c)]->end);

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

bool examine(struct tree_n *tree, char c)
{
    return tree->nodes[idx(c)] != NULL;
}

void dfs(struct tree_n *tree, int n_idx, char *word, int len, int i, int diff, int *res)
{
    if (diff > 1)
        return;

    if (i == len) {
        // word is over
        printf("line %d tree_i %d diff %d end %s\n",
                __LINE__, n_idx, diff, tree->end ? "yes" : "no");

        if (diff == 1 && tree->end) {
            (*res)++;
            printf("res++ %d\n", *res);
        }
        return;
    }

    if (examine(tree, word[i])) {
        dfs(tree->nodes[idx(word[i])], idx(word[i]), word, len, i + 1, diff, res);
        return;
    }

    for (int j = 0; j < 26; j++) {
        if (tree->nodes[j]) {
            dfs(tree->nodes[j], j, word, len, i + 1, diff + 1, res);
        }
    }
}

int walk_tree(struct tree_n *tree, char *word)
{
    int res = 0;
    dfs(tree, 0, word, strlen(word), 0, 0, &res);
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
        printf("%s done\n", words[i]);
    }

    return res;
}

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

int main()
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
