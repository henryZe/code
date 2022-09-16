#include <math.h>
#include "vos_stack.h"

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

int largestRectangleArea(int* heights, int heightsSize)
{
    int i, cur = 0, res = 0;
    VosStack *s_pos = VOS_StackCreate(NULL);
    int *l = malloc(heightsSize * sizeof(int));
    int *r = malloc(heightsSize * sizeof(int));

    for (i = 0; i < heightsSize; i++)
        // until to the end in default
        r[i] = heightsSize - 1;

    for (i = 0; i < heightsSize; i++) {
        while (!VOS_StackEmpty(s_pos) &&
                heights[VOS_StackTop(s_pos)] > heights[i]) {
            r[VOS_StackTop(s_pos)] = i - 1;
            VOS_StackPop(s_pos);
        }
        if (!VOS_StackEmpty(s_pos))
            l[i] = VOS_StackTop(s_pos);
        else
            l[i] = -1;

        VOS_StackPush(s_pos, i);
    }

    for (i = 0; i < heightsSize; i++) {
        cur = (r[i] - l[i]) * heights[i];
        printf("calc %d %d, cur %d, res %d\n", l[i], r[i], cur, res);
        res = fmax(cur, res);
    }

    return res;
}

int main(void)
{
    int h[] = {2,1,5,6,2,3};
    // int h[] = {2,4};
    printf("%d\n", largestRectangleArea(h, ARRAY_SIZE(h)));
    return 0;
}
