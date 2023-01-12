
/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2021. All rights reserved.
 * Description: 上机编程认证
 * Note: 缺省代码仅供参考，可自行决定使用、修改或删除
 */
#include <stdio.h>
// #include "securec.h"
#include <stdbool.h>
#include <stdlib.h>

#if 0
#define debug printf
#else
#define debug
#endif

#define MAX_DEPT_NUM 10
#define MAX_CAND_NUM 10000
#define MAX_EMPLOY_NUM 201

typedef struct {
    int id;             // 编号
    int employNum;      // 招聘目标
    int progmThd;       // 机考门槛值
    int techThd;        // 技面门槛值
} DeptDemand;

typedef struct {
    int id;             // 编号
    int progmGrade;     // 机试分数
    int techGrade;      // 技面分数
} Candidate;

typedef struct {
    int size;
    int employees[MAX_EMPLOY_NUM];
} DeptEmployee;

bool is_dept_hiring(int *dept_hiring, int deptNum)
{
    for (int i = 0; i < deptNum; i++) {
        if (dept_hiring[i] == 1) {
            return true;
        }
    }

    return false;
}

Candidate *p_can;
int can_idx[MAX_CAND_NUM];

int compare(const void *a, const void *b)
{
    int p_a = *(int *)a;
    int p_b = *(int *)b;

    if (p_can[p_a].techGrade == p_can[p_b].techGrade) {
        return p_can[p_b].progmGrade - p_can[p_a].progmGrade;
    }

    return p_can[p_b].techGrade - p_can[p_a].techGrade;
}

int choice_candidate(DeptDemand *deptDemands, DeptEmployee *deptEmployees,
                     Candidate *candidateAbilities, int candidateNum,
                     int *candidate_hired)
{
    int i;
    static int is_sorted = 0;
    
    if (!is_sorted) {
        p_can = candidateAbilities;
        // init can_idx
        for (i = 0; i < candidateNum; i++) {
            can_idx[i] = i;
        }
        qsort(can_idx, candidateNum, sizeof(int), compare);
        is_sorted = 1;

        debug("%d\n", __LINE__);
    }

    for (i = 0; i < candidateNum; i++) {
        debug("%d\n", __LINE__);

        if (candidate_hired[can_idx[i]]) {
            continue;
        }

        if (candidateAbilities[can_idx[i]].progmGrade < deptDemands->progmThd ||
            candidateAbilities[can_idx[i]].techGrade < deptDemands->techThd) {
                continue;
        }

        deptEmployees->employees[deptEmployees->size] = can_idx[i];
        deptEmployees->size++;

        candidate_hired[can_idx[i]] = 1;
        debug("%d idx %d\n", __LINE__, can_idx[i]);
        return can_idx[i];
    }

    // failed
    return -1;
}

// 待实现函数，在此函数中填入答题代码
// 生成的信息列表存于deptEmployees中，maxOutBufLen是最大数组长度，返回值为实际长度。
static int GetRecruitmentResult(int deptNum, DeptDemand *deptDemands, int candidateNum,
                                Candidate *candidateAbilities, DeptEmployee *deptEmployees,
                                int maxOutBufLen)
{
    int ret, i, total_hired = 0;
    int dept_hiring[MAX_DEPT_NUM];
    int candidate_hired[MAX_CAND_NUM] = {0};

    for (i = 0; i < deptNum; i++) {
        dept_hiring[i] = 1;
    }

    while ((total_hired < candidateNum) && is_dept_hiring(dept_hiring, deptNum)) {
        for (i = 0; i < deptNum; i++) {
            if (total_hired == candidateNum) {
                break;
            }

            if (dept_hiring[i] == 0) {
                continue;
            }

            debug("%d i = %d\n", __LINE__, i);
            ret = choice_candidate(deptDemands + i, deptEmployees + i, candidateAbilities, candidateNum, candidate_hired);
            if (ret < 0) {
                // no meet
                dept_hiring[i] = 0;
                continue;
            }

            if (deptEmployees[i].size == deptDemands[i].employNum) {
                // meet hc already
                dept_hiring[i] = 0;
            }
            candidate_hired[ret] = 1;
            total_hired++;
        }
    }

    debug("%d\n", __LINE__);

    // candidate request
    for (i = 0; i < deptNum; i++) {
        debug("%d\n", __LINE__);

        if (total_hired == candidateNum) {
            break;
        }

        if (deptEmployees[i].size != deptDemands[i].employNum) {
            // hc not meets yet
            continue;
        }
        
        int last_one = deptEmployees[i].employees[deptEmployees[i].size - 1];
        DeptDemand tmp = { 0, 0, candidateAbilities[last_one].progmGrade, candidateAbilities[last_one].techGrade};

        ret = choice_candidate(&tmp, deptEmployees + i, candidateAbilities, candidateNum, candidate_hired);
        if (ret < 0) {
            continue;
        }

        candidate_hired[ret] = 1;
        total_hired++;
    }

    return deptNum;
}

// 以下为考题输入输出框架，此部分代码不建议改动
static void OutputData(const DeptEmployee *deptEmployees, int outputSize)
{
    for (int i = 0; i < outputSize; i++) {
        printf("[");
        for (int j = 0; j < deptEmployees[i].size; j++) {
            printf("%s%d", ((j == 0) ? "" : " "), deptEmployees[i].employees[j]);
        }
        printf("]\n");
    }
}

int main(void)
{
    int deptNum;
    if (scanf("%d", &deptNum) != 1) { return -1; }

    static DeptDemand deptDemands[MAX_DEPT_NUM];
    for (int i = 0; i < deptNum; i++) {
        deptDemands[i].id = i;
        if (scanf("%d %d %d", &deptDemands[i].employNum,
                    &deptDemands[i].progmThd, &deptDemands[i].techThd) != 3) {
            return -1;
        }
    }

    int candidateNum;
    if (scanf("%d", &candidateNum) != 1) { return -1; }

    static Candidate candidateAbilities[MAX_CAND_NUM];
    for (int i = 0; i < candidateNum; i++) {
        candidateAbilities[i].id = i;
        if (scanf("%d %d", &candidateAbilities[i].progmGrade, &candidateAbilities[i].techGrade) != 2) {
            return -1;
        }
    }

    DeptEmployee deptEmployees[MAX_DEPT_NUM] = { 0 };
    int outputSize = GetRecruitmentResult(deptNum, deptDemands, candidateNum, candidateAbilities,
                                          deptEmployees, MAX_DEPT_NUM);

    OutputData(deptEmployees, outputSize);

    return 0;
}
