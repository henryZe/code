#define N (20000 * 1000)

int hash[N * 2] = {};

int get_count(int idx)
{
    return hash[N - idx];
}

void set_count(int idx)
{
    hash[N - idx]++;
}

// O(n)
int subarraySum(int* nums, int numsSize, int k)
{
    int i;
    int res = 0;
    int sum = 0;

    memset(hash, 0, sizeof(hash));

    set_count(sum);
    for (i = 0; i < numsSize; i++) {
        sum += nums[i];
        //                left   right
        // |-- (sum - k) --|-- k --|
        // |--        sum        --|
        res += get_count(sum - k);
        // printf("sum %d - k %d : %d\n",
        //         sum, k, get_count(sum - k));
        // printf("res = %d\n", res);
        set_count(sum);
    }

    return res;
}
