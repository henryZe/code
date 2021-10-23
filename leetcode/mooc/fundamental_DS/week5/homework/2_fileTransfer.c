#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct set {
    int parent;
};

int set_find(struct set *s, int x)
{
    // path compress
    if (s[x].parent < 0) {
        return x;
    }

    s[x].parent = set_find(s, s[x].parent);
    return s[x].parent;
}

void set_union(struct set *s, int x1, int x2)
{
    int p1 = set_find(s, x1);
    int p2 = set_find(s, x2);

    if (p1 == p2)
        return;

    if (s[p1].parent > s[p2].parent) {
        // p1 is smaller
        s[p2].parent += s[p1].parent;
        s[p1].parent = p2;
    } else {
        s[p1].parent += s[p2].parent;
        s[p2].parent = p1;
    }

    return;
}

struct set *set_init(int num)
{
    struct set *s = malloc(sizeof(struct set) * num);

    for (int i = 0; i < num; i++) {
        s[i].parent = -1;
    }

    return s;
}

int main(void)
{
    int num;
    scanf("%d", &num);

    struct set *s = set_init(num);

    char c;
    int x1, x2;
    int p1, p2;
    int components = 0;

    while (1) {
        scanf("%c", &c);
        switch (c) {
        case 'C':
            scanf("%d %d", &x1, &x2);
            p1 = set_find(s, x1 - 1);
            p2 = set_find(s, x2 - 1);
            printf("%s\n", (p1 == p2) ? "yes" : "no");
            break;

        case 'I':
            scanf("%d %d", &x1, &x2);
            set_union(s, x1 - 1, x2 - 1);
            break;

        case 'S':
            for (int i = 0; i < num; i++) {
                if (s[i].parent == -num)
                    break;
                if (s[i].parent < 0)
                    components++;
            }
            if (components > 1) {
                printf("There are %d components.\n", components);
            } else {
                printf("The network is connected.\n");
            }
            goto exit;

        default:
            break;
        }
    }

exit:
    free(s);
    return 0;
}