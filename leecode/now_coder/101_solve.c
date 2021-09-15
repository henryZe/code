int solve(int* a, int aLen )
{
    int i;
    for (i = 0; i < aLen; i++) {
        if (a[i] > i) {
            break;
        }
    }
    return i;
}