#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool visit[101][1001] = {};

int main()
{
    int ob_n;
    int kilo_max;
    int ob[101] = {};

    // please define the C input here. For example: int n; scanf("%d",&n);
    scanf("%d %d", &ob_n, &kilo_max);

    for (int i = 0; i < ob_n; i++) {
        scanf("%d", ob + i);
        // printf("%d ", ob[i]);
    }
    // printf("\n");

    bool res = false;
    // item, weight
    visit[0][0] = true;
    for (int i = 1; i <= ob_n; i++) {
        for (int j = 0; j < kilo_max; j++) {
            // printf("test i = %d j weight = %d ob[%d] = %d\n",
            //         i, j, i - 1, ob[i - 1]);

            if (visit[i - 1][j] == true) {
                // printf("i = %d j weight = %d ob[%d] = %d\n",
                //         i, j, i - 1, ob[i - 1]);

                if (j + ob[i - 1] < kilo_max) {
                    visit[i][j + ob[i - 1]] = true;

                } else if (j + ob[i - 1] == kilo_max) {
                    res = true;
                    goto out;
                }

                // no take this object
                visit[i][j] = true;
            }
        }
    }

out:
    // please define the C output here. For example: printf("%d\n",a);
    printf("%s\n", res ? "YES" : "NO");
    return 0;
}
