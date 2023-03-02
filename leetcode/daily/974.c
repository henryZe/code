int get_count(int *hash, int idx)
{
    return hash[idx];
}

void set_count(int *hash, int idx)
{
    hash[idx]++;
}

// O(n)
int subarraysDivByK(int* nums, int numsSize, int k)
{
    int res = 0;
    int sum = 0;

    int *hash = malloc(sizeof(int) * k);
    for (int i = 0; i < k; i++)
        hash[i] = 0;

    set_count(hash, 0);
    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];

        int obj = sum % k;
        // C language needs to re-process the MOD result
        if (obj < 0)
            obj += k;

        res += get_count(hash, obj);
        // printf("get_count[%d] %d res %d\n",
        //         obj, get_count(hash, obj), res);
        set_count(hash, obj);
    }

    return res;
}
