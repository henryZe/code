#include <assert.h>
#include <stdio.h>
#include "vos_map.h"

typedef struct {
    VosMap *map;
    int num;
} LogSystem;

struct stu_info {
    int id;
    int timeStamp;
};

LogSystem *LogSystemCreate(void)
{
    LogSystem *obj = malloc(sizeof(LogSystem));
    obj->map = VOS_MapCreate(NULL, NULL, NULL);
    obj->num = 0;

    return obj;
}

void LogSystemAdd(LogSystem *obj, int id, int timeStamp)
{
    VOS_MapInsert(obj->map, id, timeStamp);
    obj->num++;
}

int LogSystemDelete(LogSystem *obj, int id)
{
    VosMapIterator it = VOS_MapFind(obj->map, id);
    if (it == VOS_MapIterEnd(obj->map))
        return -1;

    VOS_MapErase(obj->map, id);
    obj->num--;
    return 0;
}

int LogSystemQuery(LogSystem *obj, int startTime, int endTime)
{
    int count = 0;
    VosMapIterator it = VOS_MapIterBegin(obj->map);

    while (it != VOS_MapIterEnd(obj->map)) {
        int time = VOS_MapIterValue(obj->map, it);
        if (startTime <= time && time <= endTime) {
            count++;
        }
        it = VOS_MapIterNext(obj->map, it);
    }

    return count;
}

void LogSystemFree(LogSystem *obj)
{
    VOS_MapDestroy(obj->map);
    free(obj);
}

struct add_info {
    int id;
    int timeStamp;
};

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

int main(void)
{
    LogSystem* obj = LogSystemCreate();
    struct add_info add_data[] = {{1,5}, {2,5}, {3,6}};

    for (int i = 0; i < ARRAY_SIZE(add_data); i++)
        LogSystemAdd(obj, add_data[i].id, add_data[i].timeStamp);

    int ret;
    ret = LogSystemQuery(obj, 5, 6);
    assert(ret == 3);

    ret = LogSystemDelete(obj, 2);
    assert(ret == 0);
    ret = LogSystemDelete(obj, 4);
    assert(ret == -1);

    ret = LogSystemQuery(obj, 5, 6);
    assert(ret == 2);

    LogSystemFree(obj);
}
