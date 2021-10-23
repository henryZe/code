#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct list {
    struct list *next;
};

int main(void)
{
    int num;
    scanf("%d", &num);

    struct list l[num + 1];
    for (int i = 1; i < num; i++) {
        l[i].next = l
    }

    int h;
    scanf("%d", &h);

    struct list *head = &(l[h]);

    int p, n;
    while (scanf("%d %d", &n, &p) != EOF) {
        struct list *pre = &(l[p]);
        struct list *next = &(l[n]);
        pre->next = next;
    }

    int d;
    scanf("%d", &d);
    struct list *del = &(l[d]);

    while (head) {
        if (head != del) {
            // if (head->next)
            printf("%ld ", head - &(l[0]));
        }
        head = head->next;
    }
    printf("\n");

    return 0;
}