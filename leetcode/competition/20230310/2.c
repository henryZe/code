
/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2022. All rights reserved.
 * Description: 上机编程认证
 * Note: 缺省代码仅供参考，可自行决定使用、修改或删除
 */
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "securec.h"

#define debug(...)

#define MAX_STR_LEN 100
#define MAX_LOG_NUM 200

/*
 * 此函数用于：拆分字符串，如 delim = " &/"，delim中的每个字符均作为分隔符进行字符串拆分
 * 输入：input表示待拆分的字符串，delim表示分隔符，bufSize表示result数组长度，result用于存放拆分后的字符串
 * 返回：拆分后的字符串数组的大小。若拆分后的字符串个数大于bufSize，返回0。
 * 例：函数调用前定义一个数组result[4][MAX_STR_LEN]，入参input = " 123 2a&7!/bcd/", delim =  " &/", bufSize = 4,
 * 调用后函数返回 4，result[0] = "123", result[1] = "2a", result[2] = "7!", result[3] = "bcd"
 */
static int SplitString(const char *input, const char *delim, int bufSize, char result[][MAX_STR_LEN])
{
    size_t len = strlen(input);
    char *str = (char*)malloc(len + 1);
    if (str == NULL) { return 0; }
    if (strncpy_s(str, len + 1, input, len) != EOK) { return 0; }

    int cnt = 0;
    char *buff = NULL;
    char *p = strtok_s(str, delim, &buff);
    while (p != NULL) {
        if (cnt >= bufSize || strcpy_s(result[cnt], MAX_STR_LEN, p) != EOK) {
            free(str);
            return 0;
        }
        p = strtok_s(NULL, delim, &buff);
        cnt++;
    }

    free(str);
    return cnt;
}

#define MAX_PROCESSID 10000
#define MAX_SUB 200

struct leaf {
    int sub[MAX_SUB];
    int sub_len;
    int father;
    bool present;
};

void insert_to_root(struct leaf *root, struct leaf *leaves, int parent)
{
    if (leaves[parent].present == false) {
        root->sub[root->sub_len++] = parent;
        debug("parent %d\n", parent);
    }

    leaves[parent].present = true;
}

void remove_from_root(struct leaf *root, struct leaf *leaves, int parent)
{
    int i;

    if (leaves[parent].father == 0) {
        int len = root->sub_len;
        for (i = 0; i < len; i++) {
            if (root->sub[i] == parent) {
                // swap the last one
                root->sub[i] = root->sub[len - 1];
                // update length
                root->sub_len--;
                break;
            }
        }
    }
}

void insert_to_leave(struct leaf *root, struct leaf *leaves,
                     int parent, int sub)
{
    // update subprocess
    leaves[sub].present = true;
    remove_from_root(root, leaves, sub);
    leaves[sub].father = parent;

    // update parent
    int len = leaves[parent].sub_len++;
    leaves[parent].present = true;
    leaves[parent].sub[len] = sub;
}

int search(struct leaf *leaves, int depth, int id)
{
    int i;
    int sum = 0;

    debug("search %d depth %d\n", id, depth);

    if (depth < 1) {
        // invalid parameter
        return 0;
    }

    if (depth == 1) {
        return 1;
    }

    for (i = 0; i < leaves[id].sub_len; i++) {
        sum += search(leaves, depth - 1, leaves[id].sub[i]);
    }

    return sum;
}

int check_num(char *num)
{
    int i = 0;
    int res = 0;

    if (num[0] == '0') {
        return -1;
    }

    for (i = 0; i < 4; i++) {
        if (num[i] == 0) {
            break;
        }

        if (isdigit(num[i]) == false) {
            return -1;
        }

        res = res * 10 + num[i] - '0';
    }

    if (num[i] != 0) {
        return -1;
    }

    return res;
}

// 待实现函数，在此函数中填入答题代码
static int LogOutput(const char logs[][MAX_STR_LEN], int num, int depth)
{
    int i;
    char result[4][MAX_STR_LEN];

    struct leaf root;
    root.sub_len = 0;

    struct leaf leaves[MAX_PROCESSID];
    for (i = 0; i < MAX_PROCESSID; i++) {
        leaves[i].sub_len = 0;
        leaves[i].father = 0;
        leaves[i].present = false;
    }

    for (i = 0; i < num; i++) {
        SplitString(logs[i], "|", 4, result);

        int parent = atoi(result[2]);
        insert_to_root(&root, leaves, parent);

        if (strncmp(result[3], "START ", 6) != 0) {
            continue;
        }

        int ctx_len = strlen(result[3]);
        if (ctx_len > 10 || ctx_len < 7) {
            continue;
        }

        char *num_str = result[3] + 6;

        int sub_id = check_num(num_str);
        if (sub_id == -1) {
            continue;
        }

        insert_to_leave(&root, leaves, parent, sub_id);
        debug("parent %d sub %d\n", parent, sub_id);
    }

    int res = 0;

    debug("root len %d\n", root.sub_len);
    for (i = 0; i < root.sub_len; i++) {
        debug("root %d\n", root.sub[i]);
        res += search(leaves, depth, root.sub[i]);
    }

    return res;
}

int main(void)
{
    int num = 0;
    if (scanf_s("%d", &num) != 1) { return -1; }

    (void)getchar();

    static char logs[MAX_LOG_NUM][MAX_STR_LEN];
    for (int i = 0; i < num; i++) {
        if (gets_s(logs[i], sizeof(logs[i])) == NULL) { return -1; }
    }

    int depth;
    if (scanf_s("%d", &depth) != 1) { return -1; }

    int result = LogOutput(logs, num, depth);
    printf("%d", result);

    return 0;
}
