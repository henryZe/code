#include "vos_str_hash.h"
#include "vos_hash.h"
#include "vos_priorityqueue.h"

#define name_length 10

typedef struct {
    VosHash *f_rating;
    VosHash *f_cuisine;
    VosHash *c_heapq;
} FoodRatings;

struct priorityElement {
    int rating;
    char *food;
};

int compare(uintptr_t data1, uintptr_t data2)
{
    struct priorityElement *d1 = (void *)data1;
    struct priorityElement *d2 = (void *)data2;

    if (d1->rating == d2->rating) {
        // min-heap
        return strcmp(d2->food, d1->food);
    }

    // max-heap
    return d1->rating - d2->rating;
}

void *priorityElement_DupFunc(void *ptr)
{
    struct priorityElement *p = malloc(sizeof(struct priorityElement));
    struct priorityElement *src = (struct priorityElement *)ptr;

    p->rating = src->rating;
    p->food = malloc(name_length);
    strcpy(p->food, src->food);
    p->food[strlen(p->food)] = 0;

    return p;
}

void priorityElement_FreeFunc(void *ptr)
{
    struct priorityElement *p = (struct priorityElement *)ptr;

    free(p->food);
    free(p);
}

void *StrValDupFunc(void *ptr)
{
    char *p = malloc(name_length);
    strcpy(p, ptr);
    p[strlen(ptr)] = 0;

    return p;
}

FoodRatings* foodRatingsCreate(char ** foods, int foodsSize,
                                char ** cuisines, int cuisinesSize,
                                int* ratings, int ratingsSize)
{
    FoodRatings *obj = malloc(sizeof(FoodRatings));
    VosHashIterator it;
    VosPriQue *heapq;
    VosDupFreeFuncPair pair = {
        priorityElement_DupFunc,
        priorityElement_FreeFunc,
    };

    VosDupFreeFuncPair keyFunc;
    keyFunc.dupFunc = StrKeyDupFunc;
    keyFunc.freeFunc = free;
    VosDupFreeFuncPair valFunc;
    valFunc.dupFunc = StrValDupFunc;
    valFunc.freeFunc = free;
    obj->f_cuisine = VOS_HashCreate(1000, VOS_HashCodeCalcStr, VOS_HashMatchStr, &keyFunc, &valFunc);
    obj->f_rating = VOS_StrHashCreate(1000);
    obj->c_heapq = VOS_StrHashCreate(1000);

    for (int i = 0; i < foodsSize; i++) {
        struct priorityElement ele = {
            .food = foods[i],
            .rating = ratings[i],
        };

        VOS_StrHashInsert(obj->f_rating, foods[i], ratings[i]);
        VOS_HashInsert(obj->f_cuisine, (uintptr_t)foods[i], (uintptr_t)cuisines[i]);

        it = VOS_StrHashFind(obj->c_heapq, cuisines[i]);
        if (it == VOS_HashIterEnd(obj->c_heapq)) {
            // empty
            // create priority queue or rb-tree map are both OK
            // here choose priority queue
            heapq = VOS_PriQueCreate(compare, &pair);
            VOS_StrHashInsert(obj->c_heapq, cuisines[i], (uintptr_t)heapq);

        } else {
            // already heapq
            heapq = (VosPriQue *)VOS_HashIterValue(obj->c_heapq, it);
        }
        VOS_PriQuePush(heapq, (uintptr_t)&ele);
    }

    return obj;
}

void foodRatingsChangeRating(FoodRatings* obj, char * food, int newRating)
{
    VOS_HashPut(obj->f_rating, (uintptr_t)food, newRating);

    VosHashIterator it_cuisine = VOS_HashFind(obj->f_cuisine, (uintptr_t)food);
    const char *cuisine = (const char *)VOS_HashIterValue(obj->f_cuisine, it_cuisine);
    VosHashIterator it = VOS_StrHashFind(obj->c_heapq, cuisine);

    VosPriQue *heapq = (VosPriQue *)VOS_HashIterValue(obj->c_heapq, it);
    struct priorityElement ele = {
        .food = food,
        .rating = newRating,
    };

    VOS_PriQuePush(heapq, (uintptr_t)&ele);
}

char * foodRatingsHighestRated(FoodRatings* obj, char * cuisine)
{
    VosHashIterator it = VOS_StrHashFind(obj->c_heapq, (const char *)cuisine);
    VosPriQue *heapq = (VosPriQue *)VOS_HashIterValue(obj->c_heapq, it);
    VosHashIterator ret;
    struct priorityElement *p;
    int p_rate, ret_rate;

    while (1) {
        p = (struct priorityElement *)VOS_PriQueTop(heapq);
        p_rate = p->rating;

        ret = VOS_StrHashFind(obj->f_rating, (const char *)p->food);
        ret_rate = VOS_HashIterValue(obj->f_rating, ret);

        if (p_rate == ret_rate)
            break;

        // pop out-date info
        VOS_PriQuePop(heapq);
    }

    return (char *)VOS_HashIterKey(obj->f_rating, ret);
}

void foodRatingsFree(FoodRatings* obj)
{
    VOS_HashDestroy(obj->f_rating);
    VOS_HashDestroy(obj->c_heapq);
    free(obj);
}

/**
 * Your FoodRatings struct will be instantiated and called as such:
 * FoodRatings* obj = foodRatingsCreate(foods, foodsSize, cuisines, cuisinesSize, ratings, ratingsSize);
 * foodRatingsChangeRating(obj, food, newRating);
 
 * char * param_2 = foodRatingsHighestRated(obj, cuisine);
 
 * foodRatingsFree(obj);
*/

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

int main(void)
{
    char *foods[] = {"kimchi", "miso", "sushi", "moussaka", "ramen", "bulgogi"};
    char *cuisines[] = {"korean", "japanese", "japanese", "greek", "japanese", "korean"};
    int ratings[] = {9, 12, 8, 15, 14, 7};

    FoodRatings* obj = foodRatingsCreate(foods, ARRAY_SIZE(foods),
                                        cuisines, ARRAY_SIZE(cuisines),
                                        ratings, ARRAY_SIZE(ratings));

    printf("%s\n", foodRatingsHighestRated(obj, "korean"));
    printf("%s\n", foodRatingsHighestRated(obj, "japanese"));

    foodRatingsChangeRating(obj, "sushi", 16);
    printf("%s\n", foodRatingsHighestRated(obj, "japanese"));

    foodRatingsChangeRating(obj, "ramen", 16);
    printf("%s\n", foodRatingsHighestRated(obj, "japanese"));

    foodRatingsFree(obj);
    return 0;
}
