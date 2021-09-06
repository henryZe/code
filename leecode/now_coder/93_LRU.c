struct node {
    int *data;
    struct node *prev;
    struct node *next;
};

void move(int b, int e, int **arr);
int get(int b, int e, int k, int **arr, int *val);

/**
 * lru design
 * @param operators int整型二维数组 the ops
 * @param operatorsRowLen int operators数组行数
 * @param operatorsColLen int* operators数组列数
 * @param k int整型 the k
 * @return int整型一维数组
 * @return int* returnSize 返回数组行数
 */
int* LRU(int** operators, int operatorsRowLen, int* operatorsColLen, int k, int* returnSize )
{
    int retLen = 0;
    int i = 0;
    int *curRow;
    int curKey, isFull = 0, isGet = 0;;
    int curIdx = 0;
    int getVal;
    int *retArr = (int *) malloc(operatorsRowLen * sizeof(int));
    struct node *curArr = malloc(k * sizeof(struct node));
    int cnt = 0;

    for (i = 0; i < operatorsRowLen; i++) {
        curRow = operators[i];
        if (curRow[0] == 1) {
            // set
            curArr[curIdx].data = curRow;
            curArr[curIdx - 1].next
            curIdx++;
            curIdx = curIdx == k ? 0 : curIdx;
            cnt++;
        } else {
            // get
            curKey = curRow[1];
            isFull = cnt >= k ? 1 : 0;
            if (isFull) {
                isGet = get(curIdx, k, curKey, curArr, &getVal);
                if (isGet) {
                    if (curIdx != 0) {
                        curRow = curArr[k - 1];
                        curArr[k - 1] = curArr[0];
                        curArr[0] = curRow;
                        move(0, curIdx, curArr);
                    }
                } else {
                    get(0, curIdx, curKey, curArr, &getVal);
                }
            } else {
                get(0, curIdx, curKey, curArr, &getVal);
            }
            retArr[retLen++] = getVal;
        }
    }
    *returnSize = retLen;
    free(curArr);
    return retArr;
}

int get(int b, int e, int k, int **arr, int *val) {
    int i;
    int *fr;
    int *cr;
    for (i = b; i < e; i++) {
        fr = arr[i];
        if (fr[1] == k) {
            *val = fr[2];
            move(i, e, k, arr);
            return 1;
        }
    }
    *val = -1;
    return 0;
}

// move from b to e - 1
void move(int b, int e, int k, int **arr) {
    int i;
    int *f = arr[b];
    for (i = b; i < e - 1; i++) {
        arr[i] = arr[i + 1];
        if (i + 1)
    }
    arr[i] = f;
}