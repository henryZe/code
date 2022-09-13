#include <math.h>
#include "vos_stack.h"

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

int largestRectangleArea(int* heights, int heightsSize)
{
    int res = 0;
    int pre_i;
    VosStack *s_height = VOS_StackCreate(NULL);
    VosStack *s_pos = VOS_StackCreate(NULL);

    VOS_StackPush(s_height, -1);
    VOS_StackPush(s_pos, -1);

    for (int i = 0; i < heightsSize; i++) {
        printf("heights[i] %d, res %d\n", heights[i], res);
        res = fmax(heights[i], res);

        while (VOS_StackTop(s_height) > heights[i]) {
            VOS_StackPop(s_height);
            VOS_StackPop(s_pos);
        }
        pre_i = VOS_StackTop(s_pos);

        printf("calc %d, res %d\n", (i - pre_i + 1) * heights[i], res);
        res = fmax((i - pre_i + 1) * heights[i], res);

        VOS_StackPush(s_height, heights[i]);
        VOS_StackPush(s_pos, i);
    }
    
    return res;
}

int main(void)
{
    int h[] = {2,1,5,6,2,3};
    printf("%d\n", largestRectangleArea(h, ARRAY_SIZE(h)));
    return 0;
}
