
/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: 上机编程认证
 * Note: 缺省代码仅供参考，可自行决定使用、修改或删除
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// #include "securec.h"

// #define debug printf
#define debug(...)

#define MAX_NUM_SIZE 100
#define NAME_BUF_LEN 11

typedef struct {
    char city[NAME_BUF_LEN];
    char departmentName[NAME_BUF_LEN];
    int personNum;
} Department;

typedef struct {
    char city[NAME_BUF_LEN];
    char departmentName[NAME_BUF_LEN];
} Result;

struct depart {
    char department[NAME_BUF_LEN];
    int num;
};

struct city {
    char city[NAME_BUF_LEN];
    int depart_num;
    struct depart departName[5 + 1];
};

int compare_city(const void *a, const void *b)
{
    struct city *city1 = (struct city *)a;
    struct city *city2 = (struct city *)b;

    return strcmp(city1->city, city2->city);
}

void insert_city(struct city *c_array, Department *input)
{
    strcpy(c_array->city, input->city);
    c_array->depart_num = 1;
    strcpy(c_array->departName[0].department,
            input->departmentName);
    c_array->departName[0].num = input->personNum;
}

int compare_depart(const void *a, const void *b)
{
    struct depart *d1 = (struct depart *)a;
    struct depart *d2 = (struct depart *)b;

    if (d1->num == d2->num) {
        return strcmp(d1->department, d2->department);
    }

    return d2->num - d1->num;
}

void insert_depart(struct city *c_array, Department *input)
{
    int idx = c_array->depart_num;

    strcpy(c_array->departName[idx].department,
            input->departmentName);
    c_array->departName[idx].num = input->personNum;

    qsort(c_array->departName, c_array->depart_num + 1,
            sizeof(struct depart), compare_depart);

    if (c_array->depart_num < 5) {
        c_array->depart_num++;
    }
}

int compare_output(const void *a, const void *b)
{
    struct depart *d1 = (struct depart *)a;
    struct depart *d2 = (struct depart *)b;

    return strcmp(d1->department, d2->department);
}

// 待实现函数，请在此填入答题代码。
// 生成的信息列表存于outBuf中，maxOutBufLen是最大数组长度，返回值为实际长度。
static int GetTopFive(Department *input, int num, Result *outBuf, int maxOutBufLen)
{
    int city_num = 0;
    struct city city_array[100];
    int i, j, k, ret, out_idx;

    for (k = 0; k < num; k++) {
        for (i = 0; i < city_num; i++) {
            if (!strcmp(input[k].city, city_array[i].city)) {
                insert_depart(city_array + i, input + k);
                break;
            }
        }

        if (i == city_num) {
            // insert new city
            debug("i = %d\n", i);
            insert_city(city_array + i, input + k);
            city_num++;
        }
    }

    qsort(city_array, city_num, sizeof(struct city), compare_city);

    debug("city_num %d\n", city_num);
    ret = 0;
    out_idx = 0;
    for (i = 0; i < city_num; i++) {
        qsort(city_array[i].departName, city_array[i].depart_num,
                sizeof(struct depart), compare_output);

        for (j = 0; j < city_array[i].depart_num; j++) {
            strcpy(outBuf[out_idx].city, city_array[i].city);
            strcpy(outBuf[out_idx].departmentName,
                    city_array[i].departName[j].department);
            out_idx++;
        }

        ret += city_array[i].depart_num;
    }

    return ret;
}

int main(void)
{
    int num;
    if (scanf("%d", &num) != 1) { return -1; }

    static Department input[MAX_NUM_SIZE];
    for (int i = 0; i < num; i++) {
        if (scanf("%s %s %d",
                    input[i].city,
                    input[i].departmentName,
                    &input[i].personNum) != 3) {
            return -1;
        }
    }

    static Result outBuf[MAX_NUM_SIZE];
    int ret = GetTopFive(input, num, outBuf, MAX_NUM_SIZE);

    for (int i = 0; i < ret; i++) {
        printf("%s %s\n", outBuf[i].city, outBuf[i].departmentName);
    }
    return 0;
}
