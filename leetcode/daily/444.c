#include <stdbool.h>

int out_degree[10001][10001];

bool sequenceReconstruction(int* nums, int numsSize,
                            int** sequences, int sequencesSize,
                            int* sequencesColSize)
{
    int i, j;
    int in_degree_count[numsSize + 1];
    int out_degree_count[numsSize + 1];

    for (i = 1; i <= numsSize; i++) {
        in_degree_count[i] = 0;
        out_degree_count[i] = 0;
    }

    int v, w;
    for (i = 0; i < sequencesSize; i++) {
        for (j = 1; j < sequencesColSize[i]; j++) {
            v = sequences[i][j - 1];
            w = sequences[i][j];

            int in_len = in_degree_count[w]++;
            int out_len = out_degree_count[v]++;
            out_degree[v][out_len] = w;
        }
    }

    int cur = 0;
    int times = 0;

    // pick up the first one's in_degree equals 0
    for (i = 1; i <= numsSize; i++) {
        if (in_degree_count[i] == 0) {
            if (cur != 0) {
                // printf("not only one: %d & %d\n", i, cur);
                // should be only one's in_degree equals 0
                return false;
            }
            cur = i;
            times++;
        }
    }

    while (cur != 0) {
        int next = 0;

        for (i = 0; i < out_degree_count[cur]; i++) {
            int v = out_degree[cur][i];
            in_degree_count[v]--;

            if (in_degree_count[v] == 0) {
                if (next != 0) {
                    // printf("next already: %d\n", next);
                    // should be only one's in_degree equals 0
                    return false;
                }

                next = v;
                times++;
            }
        }
        // printf("cur %d -> next %d\n", cur, next);
        cur = next;
    }

    if (times != numsSize) {
        // printf("length is diff: %d != %d\n", times, numsSize);
        return false;
    }

    return true;
}
