
/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2023. All rights reserved.
 * Description: 上机编程认证
 * Note: 缺省代码仅供参考，可自行决定使用、修改或删除
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "securec.h"

// #define debug printf
#define debug(...)

#define MAX_NUM_SIZE 1000
#define MAX_LINK_NODE_NUM 100
#define MAX_STR_LEN 16
#define MAX_KEY_NODE_SIZE 1000
#define MAX_ID 10001

typedef struct {
    int id;                         // 节点Id
    int size;
    int nextNodes[MAX_LINK_NODE_NUM];
} Node;

bool g[MAX_ID][MAX_ID] = {false};
bool g_rev[MAX_ID][MAX_ID] = {false};
int ret_size = 0;
bool warn[MAX_ID] = {false};

void insert(int *outBuf, int num)
{
    debug("insert %d\n", num);

    if (warn[num] == true)
        return;
    outBuf[ret_size++] = num;
    warn[num] = true;
}

bool isKeyNode(int num, int numKeyNodes, const int *keyNodes)
{
    debug("check key %d\n", num);

    for (int i = 0; i < numKeyNodes; i++) {
        if (keyNodes[i] == num) {
            return true;
        }
    }

    return false;
}

int compare(const void *a, const void *b)
{
    int int1 = *(int *)a;
    int int2 = *(int *)b;
    return int1 - int2;
}

void dfs(int v, bool graph[MAX_ID][MAX_ID], bool *visit)
{
    visit[v] = true;

    for (int i = 0; i < MAX_ID; i++) {
        if (visit[i] == true) {
            continue;
        }

        if (graph[v][i] == true) {
            dfs(i, graph, visit);
        }
    }
}

void travel_rev(int v, int numKeyNodes, const int *keyNodes, int *outBuf)
{
    bool visit[MAX_ID] = {false};

    debug("rev %d\n", v);
    if (isKeyNode(v, numKeyNodes, keyNodes)) {
        // self
        insert(outBuf, v);

        dfs(v, g_rev, visit);
        for (int i = 0; i < MAX_ID; i++) {
            if (visit[i]) {
                // insert rev
                insert(outBuf, i);
            }
        }
    }
}

// 待实现函数，请在此填入答题代码。
// 生成的信息列表存于outBuf中，outBufLen是最大数组长度，返回值为实际长度。
static int GetCheckPoints(int numNodes, const Node *nodes, int numKeyNodes, const int *keyNodes, int org,
                          int outBuf[], int outBufLen)
{
    int i, j;

    for (i = 0; i < numNodes; i++) {
        debug("size %d\n", nodes[i].size);

        for (j = 0; j < nodes[i].size; j++) {
            g[nodes[i].id][nodes[i].nextNodes[j]] = true;
            g_rev[nodes[i].nextNodes[j]][nodes[i].id] = true;
            debug("g[%d][%d] = %d\n",
                    nodes[i].id, nodes[i].nextNodes[j],
                    g[nodes[i].id][nodes[i].nextNodes[j]]);
        }
    }

    for (i = 0; i < numKeyNodes; i++)
        debug("key %d\n", keyNodes[i]);

    insert(outBuf, org);
    travel_rev(org, numKeyNodes, keyNodes, outBuf);

    bool visit[MAX_ID] = {false};
    dfs(org, g, visit);

    // travel g
    for (i = 0; i < MAX_ID; i++) {
        if (visit[i] == true) {
            travel_rev(i, numKeyNodes, keyNodes, outBuf);
        }
    }

    qsort(outBuf, ret_size, sizeof(int), compare);

    debug("ret_size %d\n", ret_size);
    return ret_size;
}

// 以下为考题输入输出框架，此部分代码不建议改动
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

static int ReadLink(Node *nodes, int numNodes)
{
    (void)getchar();

    static char buf[MAX_LINK_NODE_NUM * MAX_STR_LEN];
    for (int i = 0; i < numNodes; i++) {
        if (gets_s(buf, sizeof(buf)) == NULL) { return -1; }

        if (sscanf_s(buf, "%d", &nodes[i].id) != 1) { return -1; }

        char *tmp = strstr(buf, ":");
        if (tmp == NULL) { return -1; }
        tmp++;

        char nextNodes[MAX_LINK_NODE_NUM][MAX_STR_LEN];
        nodes[i].size = SplitString(tmp, " ", MAX_LINK_NODE_NUM, nextNodes);

        for (int j = 0; j < nodes[i].size; ++j) {
            nodes[i].nextNodes[j] = (int)strtol(nextNodes[j], NULL, 10);
        }
    }
    return 0;
}

int main(void)
{
    int numNodes;
    if (scanf("%d", &numNodes) != 1) { return -1; }

    static Node nodes[MAX_NUM_SIZE];
    if (ReadLink(nodes, numNodes) == -1) { return -1; }

    int numKeyNodes = 0;
    if (scanf("%d", &numKeyNodes) != 1) { return -1; }

    static int keyNodes[MAX_KEY_NODE_SIZE];
    for (int i = 0; i < numKeyNodes; i++) {
        if (scanf("%d", &keyNodes[i]) != 1) { return -1; }
    }

    int org;
    if (scanf("%d", &org) != 1) { return -1; }

    int outBuf[MAX_NUM_SIZE] = { 0 };
    int outBufSize = GetCheckPoints(numNodes, nodes, numKeyNodes, keyNodes, org, outBuf, MAX_NUM_SIZE);

    for (int i = 0; i < outBufSize; i++) {
        printf("%s%d", (i == 0 ? "" : " "), outBuf[i]);
    }

    return 0;
}
