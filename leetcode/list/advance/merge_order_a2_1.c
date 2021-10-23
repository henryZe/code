#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* merge2Lists(struct ListNode *l1, struct ListNode *l2)
{
    if ((!l1) || (!l2))
        return l1 ? l1 : l2;

    struct ListNode temp = {
        .val = 0,
        .next = NULL,
    };

    struct ListNode *head = &temp;
    struct ListNode *node = &temp;

    while (l1 && l2) {
        if (l1->val <= l2->val) {
            node->next = l1;
            l1 = l1->next;
        } else {
            node->next = l2;
            l2 = l2->next;
        }
        node = node->next;
    }

    if (!l1) {
        node->next = l2;
    } else {
        node->next = l1;
    }

    return head->next;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize)
{
    if (!listsSize)
        return NULL;

    int interval = 1;
    int i;

    while (interval < listsSize) {
        for (i = 0; i < listsSize - interval; i += interval * 2) {
            lists[i] = merge2Lists(lists[i], lists[i + interval]);
        }
        interval *= 2;
    }

    return lists[0];
}

int main(void)
{
    struct ListNode *res;

    // struct ListNode l02 = {
    //     .val = 5,
    //     .next = NULL,
    // };
    // struct ListNode l01 = {
    //     .val = 4,
    //     .next = &l02,
    // };
    // struct ListNode l0 = {
    //     .val = 1,
    //     .next = &l01,
    // };

    // struct ListNode l12 = {
    //     .val = 4,
    //     .next = NULL,
    // };
    // struct ListNode l11 = {
    //     .val = 3,
    //     .next = &l12,
    // };
    // struct ListNode l1 = {
    //     .val = 1,
    //     .next = &l11,
    // };

    // struct ListNode l21 = {
    //     .val = 6,
    //     .next = NULL,
    // };
    // struct ListNode l2 = {
    //     .val = 2,
    //     .next = &l21,
    // };

    struct ListNode l06 = {
        .val = 0,
        .next = NULL,
    };
    struct ListNode l05 = {
        .val = -1,
        .next = &l06,
    };
    struct ListNode l04 = {
        .val = -1,
        .next = &l05,
    };
    struct ListNode l03 = {
        .val = -3,
        .next = &l04,
    };
    struct ListNode l02 = {
        .val = -9,
        .next = &l03,
    };
    struct ListNode l01 = {
        .val = -9,
        .next = &l02,
    };
    struct ListNode l0 = {
        .val = -10,
        .next = &l01,
    };

    struct ListNode l1 = {
        .val = -5,
        .next = NULL,
    };

    struct ListNode l2 = {
        .val = 4,
        .next = NULL,
    };

    struct ListNode l3 = {
        .val = -8,
        .next = NULL,
    };

    struct ListNode l56 = {
        .val = 3,
        .next = NULL,
    };
    struct ListNode l55 = {
        .val = 2,
        .next = &l56,
    };
    struct ListNode l54 = {
        .val = -2,
        .next = &l55,
    };
    struct ListNode l53 = {
        .val = -4,
        .next = &l54,
    };
    struct ListNode l52 = {
        .val = -5,
        .next = &l53,
    };
    struct ListNode l51 = {
        .val = -6,
        .next = &l52,
    };
    struct ListNode l5 = {
        .val = -9,
        .next = &l51,
    };

    struct ListNode l64 = {
        .val = 0,
        .next = NULL,
    };
    struct ListNode l63 = {
        .val = -1,
        .next = &l64,
    };
    struct ListNode l62 = {
        .val = -2,
        .next = &l63,
    };
    struct ListNode l61 = {
        .val = -3,
        .next = &l62,
    };
    struct ListNode l6 = {
        .val = -3,
        .next = &l61,
    };

    struct ListNode *list[] = {&l0, &l1, &l2, &l3, NULL, &l5, &l6};
    res = mergeKLists(list, sizeof(list)/sizeof(list[0]));

    while (res) {
        printf("%d -> ", res->val);
        res = res->next;
    }

    return 0;
}
