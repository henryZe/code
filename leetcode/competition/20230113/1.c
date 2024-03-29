
/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: 上机编程认证
 * Note: 缺省代码仅供参考，可自行决定使用、修改或删除
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "securec.h"

// #define debug printf
#define debug(...)

#define MAX_NUM_SIZE 100
#define NAME_BUF_LEN 11
#define MAX_DEPART_NUM 5

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
    int persons;
};

struct city {
    char city[NAME_BUF_LEN];
    int depart_num;
    struct depart departName[MAX_DEPART_NUM + 1];
};

int compare_city(const void *a, const void *b)
{
    struct city *city1 = (struct city *)a;
    struct city *city2 = (struct city *)b;

    return strcmp(city1->city, city2->city);
}

int compare_person(const void *a, const void *b)
{
    struct depart *d1 = (struct depart *)a;
    struct depart *d2 = (struct depart *)b;

    if (d1->persons == d2->persons)
        return strcmp(d1->department, d2->department);

    return d2->persons - d1->persons;
}

void insert_depart(struct city *c_array, Department *input)
{
    int idx = c_array->depart_num;

    strcpy_s(c_array->departName[idx].department, NAME_BUF_LEN,
            input->departmentName);
    c_array->departName[idx].persons = input->personNum;

    qsort(c_array->departName, c_array->depart_num + 1,
            sizeof(struct depart), compare_person);

    if (c_array->depart_num < MAX_DEPART_NUM)
        c_array->depart_num++;
}

void insert_city(struct city *c_array, Department *input)
{
    strcpy_s(c_array->city, NAME_BUF_LEN, input->city);
    insert_depart(c_array, input);
}

int compare_depart(const void *a, const void *b)
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

    for (int k = 0; k < num; k++) {
        int i;
        for (i = 0; i < city_num; i++) {
            if (!strcmp(input[k].city, city_array[i].city)) {
                insert_depart(city_array + i, input + k);
                break;
            }
        }

        // new city
        if (i == city_num) {
            debug("i = %d\n", i);
            insert_city(city_array + i, input + k);
            city_num++;
        }
    }

    qsort(city_array, city_num, sizeof(struct city), compare_city);
    debug("city_num %d\n", city_num);

    int out_idx = 0;
    for (int i = 0; i < city_num; i++) {
        qsort(city_array[i].departName, city_array[i].depart_num,
                sizeof(struct depart), compare_depart);

        for (int j = 0; j < city_array[i].depart_num; j++) {
            strcpy_s(outBuf[out_idx].city, NAME_BUF_LEN,
                    city_array[i].city);
            strcpy_s(outBuf[out_idx].departmentName, NAME_BUF_LEN,
                    city_array[i].departName[j].department);
            out_idx++;
        }
    }

    return out_idx;
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
