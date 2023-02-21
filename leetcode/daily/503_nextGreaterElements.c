/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
// O(n^2)
// int* nextGreaterElements(int* nums, int numsSize, int* returnSize)
// {
//     int i, j;
//     int *res = malloc(numsSize * sizeof(int));
//
//     for (i = 0; i < numsSize; i++) {
//         res[i] = -1;
//     }
//
//     for (i = 0; i < numsSize; i++) {
//         for (j = i + 1; j < 2 * numsSize; j++) {
//             if (nums[i] < nums[j % numsSize]) {
//                 res[i] = nums[j % numsSize];
//                 break;
//             }
//         }
//     }
//
//     *returnSize = numsSize;
//     return res;
// }

// O(n)
int* nextGreaterElements(int* nums, int numsSize, int* returnSize)
{
    int i, j;
    int *res = malloc(numsSize * sizeof(int));

    for (i = 0; i < numsSize; i++) {
        res[i] = -1;
    }

    int stk_size = 0;
    int *stk = malloc(numsSize * 2 * sizeof(int));

    for (i = 0; i < 2 * numsSize; i++) {
        int idx = i % numsSize;

        while (stk_size > 0 && nums[stk[stk_size - 1]] < nums[idx]) {
            res[stk[stk_size - 1]] = nums[idx];
            // pop
            stk_size -= 1;
        }

        // push
        stk_size++;
        stk[stk_size - 1] = idx;
    }

    *returnSize = numsSize;
    return res;
}
