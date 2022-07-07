#include <stdio.h>
#include <assert.h>
#include "vos_int_hash.h"
#include "vos_priorityqueue.h"
#include "vos_queue.h"

struct heapq_mem {
    int count;
    char c;
};

int32_t heaq_compare(uintptr_t data1, uintptr_t data2)
{
    struct heapq_mem *mem1 = (struct heapq_mem *)data1;
    struct heapq_mem *mem2 = (struct heapq_mem *)data2;

    return mem1->count - mem2->count;
}

VosHash *create_input_hash(char *input)
{
    int i;
    VosHashIterator it;
    VosHash *hash = VOS_IntHashCreate(256);

    for (i = 0; input[i]; i++) {
        it = VOS_IntHashFind(hash, input[i]);

        if (it == VOS_HashIterEnd(hash)) {
            VOS_HashInsert(hash, input[i], 1);
        } else {
            VOS_HashPut(hash, input[i], VOS_HashIterValue(hash, it) + 1);
        }
    }

    return hash;
}

VosPriQue *init_output_heapq(VosHash *hash)
{
    struct heapq_mem *mem;
    VosHashIterator it;
    VosPriQue *heapq = VOS_PriQueCreate(heaq_compare, NULL);

    it = VOS_HashIterBegin(hash);
    while (it != VOS_HashIterEnd(hash)) {
        mem = malloc(sizeof(struct heapq_mem));
        mem->count = VOS_HashIterValue(hash, it);
        mem->c = VOS_HashIterKey(hash, it);

        VOS_PriQuePush(heapq, (uintptr_t)mem);

        it = VOS_HashIterNext(hash, it);
    }

    return heapq;
}

char *generate_new_string(VosPriQue *heapq, int interval, size_t s_len)
{
    int i;
    struct heapq_mem *mem, *queue_mem;
    VosQueue *queue = VOS_QueueCreate(interval - 1, NULL);

    char *res = malloc(s_len + 1);
    // memset_s(res, s_len + 1, 0, s_len + 1);
    memset(res, 0, s_len + 1);

    i = 0;
    while (VOS_PriQueSize(heapq)) {
        mem = (struct heapq_mem *)VOS_PriQueTop(heapq);
        // printf("heapq pop %c %d\n", mem->c, mem->count);
        VOS_PriQuePop(heapq);

        // printf("queue size %ld\n", VOS_QueueSize(queue));
        if (VosQueFull(queue)) {
            queue_mem = (struct heapq_mem *)VOS_QueueFront(queue);
            // printf("queue pop: %c %d\n", queue_mem->c, queue_mem->count);
            VOS_QueuePop(queue);

            if (queue_mem->count) {
                // printf("heapq push %c %d\n", queue_mem->c, queue_mem->count);
                VOS_PriQuePush(heapq, (uintptr_t)queue_mem);
            }
        }

        res[i++] = mem->c;
        // printf("cur %s\n", res);
        mem->count--;
        // printf("queue push: c %c count %d\n", mem->c, mem->count);
        VOS_QueuePush(queue, (uintptr_t)mem);
    }

    if (strlen(res) != s_len)
        return "";

    return res;
}

char *CombineChars(char *input, int interval)
{
    if (interval < 2)
        return input;

    VosHash *hash = create_input_hash(input);
    VosPriQue *heapq = init_output_heapq(hash);

    return generate_new_string(heapq, interval, strlen(input));
}

int main(void)
{
    // char *src = "xxyyzz";
    // int interval = 3;
    // char *src = "xxxyyz";
    // int interval = 3;
    char *src = "aaazxxyy";
    int interval = 2;
    // char *src = "";
    // int interval = 2;
    // char *src = "aaazxxyy";
    // int interval = 1;

    char *ret;
    ret = CombineChars(src, interval);
    printf("%s\n", ret);
    return 0;
}
