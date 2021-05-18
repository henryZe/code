#include <stdlib.h>
#include <stdio.h>

struct info {
    int *scores;
    int total_score;
    int perfect_count;
};

static struct info *infos = NULL;

int compare_index(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int compare_perfect_count(const void *a, const void *b)
{
    int res = infos[*(int *)b].perfect_count - infos[*(int *)a].perfect_count;

    // printf("perfect %d:%d %d:%d\n",
    //         *(int *)a, infos[*(int *)a].perfect_count,
    //         *(int *)b, infos[*(int *)b].perfect_count);

    if (res == 0)
        return compare_index(a, b);

    return res;
}

int compare_total_score(const void *a, const void *b)
{
    int res = infos[*(int *)b].total_score - infos[*(int *)a].total_score;

    // printf("total %d:%d %d:%d\n",
    //         *(int *)a, infos[*(int *)a].total_score,
    //         *(int *)b, infos[*(int *)b].total_score);

    if (res == 0)
        return compare_perfect_count(a, b);

    return res;
}

int main(void)
{
    int students, problems, submissions;
    scanf("%d %d %d\n", &students, &problems, &submissions);

    int *scores = malloc(sizeof(int) * (problems + 1));
    for (int i = 1; i <= problems; i++) {
        scanf("%d ", scores + i);
    }

    infos = malloc(sizeof(struct info) * (students + 1));

    for (int i = 1; i <= students; i++) {
        infos[i].scores = malloc(sizeof(int) * (problems + 1));
        infos[i].total_score = -1;
        infos[i].perfect_count = 0;

        for (int j = 1; j <= problems; j++) {
            // -2 never submit yet, -1 means not pass compiler
            infos[i].scores[j] = -2;
        }
    }

    int id, problem_id, score;

    for (int i = 0; i < submissions; i++) {
        scanf("%d %d %d\n", &id, &problem_id, &score);

        if (score > infos[id].scores[problem_id]) {
            infos[id].scores[problem_id] = score;
        }
    }

    for (int i = 1; i <= students; i++) {
        for (int j = 1; j <= problems; j++) {
            // success to pass compiler
            if (infos[i].scores[j] >= 0) {
                if (infos[i].total_score < 0) {
                    infos[i].total_score = 0;
                }

                infos[i].total_score += infos[i].scores[j];

                if (infos[i].scores[j] == scores[j]) {
                    infos[i].perfect_count++;
                }
            }
        }
    }

    int *rank = malloc(sizeof(int) * (students + 1));
    for (int i = 1; i <= students; i++) {
        rank[i] = i;
    }

    qsort(rank + 1, students, sizeof(int), compare_total_score);

    for (int i = 1, rank_id = 1; i <= students; i++) {

        if (infos[rank[i]].total_score < 0)
            continue;

        printf("%d %05d %d ", rank_id, rank[i], infos[rank[i]].total_score);

        for (int j = 1; j <= problems; j++) {
            if (infos[rank[i]].scores[j] == -2)
                printf("-");
            else if (infos[rank[i]].scores[j] == -1)
                printf("0");
            else
                printf("%d", infos[rank[i]].scores[j]);

            if (j == problems)
                printf("\n");
            else
                printf(" ");
        }

        if (infos[rank[i]].total_score != infos[rank[i + 1]].total_score)
            rank_id = i + 1;
    }

    return 0;
}
