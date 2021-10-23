#include <stdio.h>
#include <string.h>
#include <limits.h>

enum CARD_TYPE {
    single = 1,
    twin,
    triple,
    bomb,
    quintuple,
    joker_bomb,
};

struct state {
    char card[32];
    enum CARD_TYPE type;
    int most_sign;
};

char *ref = "345678910JQKA2jokerJOKER";

#define JOKER_POS (strstr(ref, "2") - ref)

int most_significant(char *p)
{
    return strstr(ref, p) - ref;
}

int parse_word(char *curr, struct state *s, char *next)
{
    char *p;
    enum CARD_TYPE type = single;
    int most_sign = INT_MAX;
    char c;

    memset(s->card, 0, sizeof(s->card));

    do {
        p = strstr(curr, "-");
        if (p) {
            *p = 0;
            if (next) {
                strcpy(next, p + 1);
            }
        } else {
            if (scanf("%c", &c) == EOF)
                break;
        }

        strcat(s->card, curr);

        if (most_sign == INT_MAX)
            most_sign = most_significant(curr);

        if (p)
            // next card
            break;

        if (c == '\n') {
            break;
        }

        if (c == ' ') {
            type++;
            strcat(s->card, " ");
        }
    } while (scanf("%[^' '\n]", curr) != EOF);

    if (type == twin) {
        if (most_sign > JOKER_POS) {
            type = joker_bomb;
        }
    }
    s->type = type;
    s->most_sign = most_sign;
    return 0;
}

int compare_sign(struct state *s1, struct state *s2)
{
    return s1->most_sign - s2->most_sign;
}

int compare(struct state *s1, struct state *s2)
{
    if (s1->type == s2->type)
        return compare_sign(s1, s2);

    if (s1->type == joker_bomb)
        return 1;

    if (s2->type == joker_bomb)
        return -1;

    if (s1->type == bomb)
        return 1;

    if (s2->type == bomb)
        return -1;

    // printf("line %d\n", __LINE__);
    // error
    return 0;
}

int main(void)
{
    char curr[32];
    char next[32];
    struct state s1;
    struct state s2;

    while (scanf("%s", curr) != EOF) {
        parse_word(curr, &s1, next);
        // printf("card1: %d %d\n", s1.type, s1.most_sign);
        parse_word(next, &s2, NULL);
        // printf("card2: %d %d\n", s2.type, s2.most_sign);

        int ret = compare(&s1, &s2);
        if (ret > 0) {
            printf("%s\n", s1.card);
        } else if (ret < 0) {
            printf("%s\n", s2.card);
        } else {
            printf("ERROR\n");
        }
    }

    return 0;
}
