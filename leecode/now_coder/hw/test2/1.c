#include <stdio.h>

int query(int *score, int start, int end)
{
    int temp;
    if (end < start) {
        temp = end;
        end = start;
        start = temp;
    }

    int max = score[start];
    for (int i = start; i <= end; i++) {
        if (score[i] > max) {
            max = score[i];
        }
    }

    return max;
}

void update(int *score, int index, int s)
{
    score[index] = s;
}

int main(void)
{
    int st_num, op_num, s;
    int score[30001];

    while (scanf("%d %d\n", &st_num, &op_num) != EOF) {
        for (int i = 1; i <= st_num; i++) {
            scanf("%d ", &s);
            score[i] = s;
        }

        char op;
        int start, end, index;
        
        while (op_num-- > 0) {
            scanf("%c ", &op);

            switch (op) {
            case 'Q':
                scanf("%d %d\n", &start, &end);
                printf("%d\n", query(score, start, end));
                break;

            case 'U':
                scanf("%d %d\n", &index, &s);
                update(score, index, s);
                break;

            default:
                break;
            }
        }
    }

    return 0;
}
