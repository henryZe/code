/* from https://github.com/vy/libpqueue
 * Copyright (c) 2014, Volkan Yazıcı <volkan.yazici@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


/**
 * @file  pqueue.h
 * @brief Priority Queue function declarations
 *
 * @{
 */


#ifndef PQUEUE_H
#define PQUEUE_H
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** priority data type */
typedef unsigned long long pqueue_pri_t;
//extern void set_pri(void *a, pqueue_pri_t pri);
//extern void set_pos(void *a, size_t pos);


/** callback functions to get/set/compare the priority of an element */
typedef pqueue_pri_t (*pqueue_get_pri_f)(void *a);
typedef void (*pqueue_set_pri_f)(void *a, pqueue_pri_t pri);

// zhangqiang:原来的比较优先级的函数不能满足要求，需要比较节点
//typedef int (*pqueue_cmp_pri_f)(pqueue_pri_t next, pqueue_pri_t curr);
typedef int (*pqueue_cmp_node_f)(void *priQueue, void *node1, void *node2);


/** callback functions to get/set the position of an element */
typedef size_t (*pqueue_get_pos_f)(void *a);
typedef void (*pqueue_set_pos_f)(void *a, size_t pos);


// /** debug callback function to print a entry */
// typedef void (*pqueue_print_entry_f)(FILE *out, void *a);


/** the priority queue handle */
typedef struct pqueue_t
{
    size_t size;                /**< number of elements in this queue */
    size_t avail;               /**< slots available in this queue */
    size_t step;                /**< growth stepping setting */
    //pqueue_cmp_pri_f cmppri;    /**< callback to compare nodes */
    pqueue_cmp_node_f cmpnode;    /**< callback to compare nodes */
    pqueue_get_pri_f getpri;    /**< callback to get priority of a node */
    pqueue_set_pri_f setpri;    /**< callback to set priority of a node */
    pqueue_get_pos_f getpos;    /**< callback to get position of a node */
    pqueue_set_pos_f setpos;    /**< callback to set position of a node */
    void **d;                   /**< The actualy queue in binary heap form */

    void *priQueue;
} pqueue_t;

// pqueue.c
#define left(i)   ((i) << 1)
#define right(i)  (((i) << 1) + 1)
#define parent(i) ((i) >> 1)


static inline pqueue_t *
pqueue_init(size_t n,
            pqueue_cmp_node_f cmpnode,
            pqueue_get_pri_f getpri,
            pqueue_set_pri_f setpri,
            pqueue_get_pos_f getpos,
            pqueue_set_pos_f setpos,
            void *priQueue)
{
    pqueue_t *q;

    if (!(q = (pqueue_t*)malloc(sizeof(pqueue_t))))
        return NULL;

    /* Need to allocate n+1 elements since element 0 isn't used. */
    if (!(q->d = (void**)malloc((n + 1) * sizeof(void *)))) {
        free(q);
        return NULL;
    }

    q->size = 1;
    q->avail = q->step = (n+1);  /* see comment above about n+1 */
    q->cmpnode = cmpnode;
    q->setpri = setpri;
    q->getpri = getpri;
    q->getpos = getpos;
    q->setpos = setpos;
    q->priQueue = priQueue; // 含义由调用者决定

    return q;
}

static inline void pqueue_clear(pqueue_t *q)
{
    //memset(q->d, sizeof(q->d));
    q->size = 1;
}

static inline void
pqueue_free(pqueue_t *q)
{
    free(q->d);
    free(q);
}

static inline size_t
pqueue_size(pqueue_t *q)
{
    /* queue element 0 exists but doesn't count since it isn't used. */
    return (q->size - 1);
}

static inline void
bubble_up(pqueue_t *q, size_t i)
{
    size_t parent_node;
    void *moving_node = q->d[i];
    //pqueue_pri_t moving_pri = q->getpri(moving_node);

    // for (parent_node = parent(i);
    //      ((i > 1) && q->cmppri(q->getpri(q->d[parent_node]), moving_pri));
    //      i = parent_node, parent_node = parent(i))
    for (parent_node = parent(i); (i > 1) && (q->cmpnode(q->priQueue, q->d[parent_node], moving_node) <= 0);
         i = parent_node, parent_node = parent(i))
    {
        q->d[i] = q->d[parent_node];
        q->setpos(q->d[i], i);
    }

    q->d[i] = moving_node;
    q->setpos(moving_node, i);
}


static inline size_t
maxchild(pqueue_t *q, size_t i)
{
    size_t child_node = left(i);

    if (child_node >= q->size)
        return 0;

    // if ((child_node+1) < q->size &&
    //     q->cmppri(q->getpri(q->d[child_node]), q->getpri(q->d[child_node+1])))
    if ((child_node+1) < q->size && q->cmpnode(q->priQueue, q->d[child_node], q->d[child_node + 1]) <= 0)
        child_node++; /* use right child instead of left */

    return child_node;
}


static inline void
percolate_down(pqueue_t *q, size_t i)
{
    size_t child_node;
    void *moving_node = q->d[i];
    //pqueue_pri_t moving_pri = q->getpri(moving_node);

    // while ((child_node = maxchild(q, i)) &&
    //        q->cmppri(moving_pri, q->getpri(q->d[child_node])))
    while ((child_node = maxchild(q, i)) &&
           q->cmpnode(q->priQueue, moving_node, q->d[child_node]) <= 0)
    {
        q->d[i] = q->d[child_node];
        q->setpos(q->d[i], i);
        i = child_node;
    }

    q->d[i] = moving_node;
    q->setpos(moving_node, i);
}


static inline int
pqueue_insert(pqueue_t *q, void *d)
{
    void *tmp;
    size_t i;
    size_t newsize;

    if (!q) return 1;

    /* allocate more memory if necessary */
    if (q->size >= q->avail) {
        newsize = q->size + q->step;
        if (!(tmp = realloc(q->d, sizeof(void *) * newsize)))
            return 1;
        q->d = (void**)tmp;
        q->avail = newsize;
    }

    /* insert item */
    i = q->size++;
    q->d[i] = d;
    bubble_up(q, i);

    return 0;
}


// void
// pqueue_change_priority(pqueue_t *q,
//                        pqueue_pri_t new_pri,
//                        void *d)
// {
//     size_t posn;
//     pqueue_pri_t old_pri = q->getpri(d);

//     q->setpri(d, new_pri);
//     posn = q->getpos(d);
//     if (q->cmppri(old_pri, new_pri))
//         bubble_up(q, posn);
//     else
//         percolate_down(q, posn);
// }


// int
// pqueue_remove(pqueue_t *q, void *d)
// {
//     size_t posn = q->getpos(d);
//     q->d[posn] = q->d[--q->size];
//     if (q->cmppri(q->getpri(d), q->getpri(q->d[posn])))
//         bubble_up(q, posn);
//     else
//         percolate_down(q, posn);

//     return 0;
// }


static inline void *
pqueue_pop(pqueue_t *q)
{
    void *head;

    if (!q || q->size == 1)
        return NULL;

    head = q->d[1];
    q->d[1] = q->d[--q->size];
    percolate_down(q, 1);

    return head;
}


static inline void *
pqueue_peek(pqueue_t *q)
{
    void *d;
    if (!q || q->size == 1)
        return NULL;
    d = q->d[1];
    return d;
}


// void
// pqueue_dump(pqueue_t *q,
//             FILE *out,
//             pqueue_print_entry_f print)
// {
//     int i;

//     fprintf(stdout,"posn\tleft\tright\tparent\tmaxchild\t...\n");
//     for (i = 1; i < q->size ;i++) {
//         fprintf(stdout,
//                 "%d\t%d\t%d\t%d\t%ul\t",
//                 i,
//                 left(i), right(i), parent(i),
//                 (unsigned int)maxchild(q, i));
//         print(out, q->d[i]);
//     }
// }

// static void
// set_pos(void *d, size_t val)
// {
//     /* do nothing */
// }


// static void
// set_pri(void *d, pqueue_pri_t pri)
// {
//     /* do nothing */
// }


// void
// pqueue_print(pqueue_t *q,
//              FILE *out,
//              pqueue_print_entry_f print)
// {
//     pqueue_t *dup;
// 	void *e;

//     dup = pqueue_init(q->size,
//                       q->cmppri, q->getpri, set_pri,
//                       q->getpos, set_pos);
//     dup->size = q->size;
//     dup->avail = q->avail;
//     dup->step = q->step;

//     memcpy(dup->d, q->d, (q->size * sizeof(void *)));

//     while ((e = pqueue_pop(dup)))
// 		print(out, e);

//     pqueue_free(dup);
// }


// static int
// subtree_is_valid(pqueue_t *q, int pos)
// {
//     if (left(pos) < q->size) {
//         /* has a left child */
//         if (q->cmppri(q->getpri(q->d[pos]), q->getpri(q->d[left(pos)])))
//             return 0;
//         if (!subtree_is_valid(q, left(pos)))
//             return 0;
//     }
//     if (right(pos) < q->size) {
//         /* has a right child */
//         if (q->cmppri(q->getpri(q->d[pos]), q->getpri(q->d[right(pos)])))
//             return 0;
//         if (!subtree_is_valid(q, right(pos)))
//             return 0;
//     }
//     return 1;
// }


// int
// pqueue_is_valid(pqueue_t *q)
// {
//     return subtree_is_valid(q, 1);
// }


#endif /* PQUEUE_H */
/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */