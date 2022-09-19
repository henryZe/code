#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int activityId;
    int startDate;
    int endDate;
    int category;
    int number;
    int priceLimit;
    int discount;
} Activity;

#define MAX_CNT 101
#define EMPTY 0
#define EXIST 1

typedef struct {
        int cate_num[MAX_CNT];
        int *cate_pri[MAX_CNT];

        int ac_state[MAX_CNT];
        Activity ac[MAX_CNT];
} PromotionSys;

PromotionSys g_sys;

PromotionSys *PromotionSysCreate()
{
        int i;
        PromotionSys *sys = &g_sys;

        for (i = 0; i < MAX_CNT; i++) {
                sys->cate_num[i] = 0;
                sys->cate_pri[i] = malloc(sizeof(int) * MAX_CNT);
                sys->ac_state[i] = EMPTY;
        }

        return sys;
}

int compare(const void *data1, const void *data2)
{
        int id1 = *(int *)data1;
        int id2 = *(int *)data2;

        printf("id1 %d id2 %d\n", id1, id2);

        // max -> min
        if (g_sys.ac[id1].discount != g_sys.ac[id2].discount)
                return g_sys.ac[id2].discount - g_sys.ac[id1].discount;

        // min -> max
        if (g_sys.ac[id1].endDate != g_sys.ac[id2].endDate)
                return g_sys.ac[id1].endDate - g_sys.ac[id2].endDate;

        // min -> max
        return id1 - id2;
}

bool PromotionSysAddPromotion(PromotionSys *sys,
                                Activity *activity)
{
        int id = activity->activityId;

        if (!sys)
                return false;

        if (sys->ac_state[id] == EXIST)
                return false;

        sys->ac_state[id] = EXIST;
        sys->ac[id] = *activity;

        int cate_num = sys->cate_num[activity->category];
        sys->cate_pri[activity->category][cate_num] = id;
        sys->cate_num[activity->category]++;

        return true;
}

int PromotionSysProcessPromotion(PromotionSys *sys, int date,
                                int category, int price)
{
        if (!sys->cate_num[category])
                return price;

        qsort(sys->cate_pri[category],
                sys->cate_num[category], sizeof(int), compare);

        int id;
        for (int i = 0; i < sys->cate_num[category]; i++) {

                id = sys->cate_pri[category][i];
                if (sys->ac[id].endDate < date)
                        continue;

                if (!sys->ac[id].number)
                        continue;

                if (sys->ac[id].priceLimit > price)
                        continue;

                sys->ac[id].number--;
                return price - sys->ac[id].discount;
        }

        return price;
}

int PromotionSysQueryRemainingNum(PromotionSys *sys,
                                int date, int activityId)
{
        if (sys->ac[activityId].startDate <= date && sys->ac[activityId].endDate >= date)
                return sys->ac[activityId].number;
        return 0;
}

void PromotionSysFree(PromotionSys *sys)
{
        return;
}