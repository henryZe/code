/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: 上机编程认证
 * Note: 缺省代码仅供参考，可自行决定使用、修改或删除
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
// #include "securec.h"

// 用例足够使用
#define BUF_LEN 64
#define OUT_BUF_LEN 64
#define TOTAL_SIZE 100

struct m_block {
    int size;
    int addr;
    struct m_block *next;
};

struct m_block alloc_head = {};
struct m_block free_head = {};

struct m_block *alloc_mblock(int addr, int memSize)
{
    struct m_block *alloc;

    alloc = malloc(sizeof(struct m_block));
    alloc->addr = addr;
    alloc->size = memSize;
    alloc->next = 0;

    return alloc;
}

void insertlist(struct m_block *head, struct m_block *b)
{
    struct m_block *prev = head, *cur = head->next;
    while (cur) {
        if (cur->addr > b->addr) {
            // insert
            b->next = prev->next;
            prev->next = b;
            return;
        }

        prev = cur;
        cur = cur->next;
    }

    // insert
    b->next = 0;
    prev->next = b;
}

// 在此添加你的代码
void MemPoolInit(void)
{
    insertlist(&free_head, alloc_mblock(0, TOTAL_SIZE));
}

void freelist(struct m_block *head)
{
    struct m_block *next;
    struct m_block *cur = head->next;

    while (cur) {
        next = cur->next;
        free(cur);
        cur = next;
    }
}

// 在此添加你的代码
void MemPoolDeinit(void)
{
    freelist(&alloc_head);
    freelist(&free_head);
}

/* 返回分配的内存首地址，失败返回 -1，框架会自动输出"error" */
int MemPoolRequest(int memSize)
{
    int addr;
    struct m_block *tmp;
    struct m_block *prev = &free_head, *cur = free_head.next;

    // 在此添加你的代码
    while (cur) {
        if (cur->size == memSize) {
            // remove cur from free_list
            addr = cur->addr;
            prev->next = cur->next;

            // insert cur into alloc_list
            insertlist(&alloc_head, cur);
            return addr;

        } else if (cur->size > memSize) {
            // split

            // update cur of free_list
            addr = cur->addr;
            cur->addr = addr + memSize;
            cur->size -= memSize;

            // insert addr into alloc_list
            tmp = alloc_mblock(addr, memSize);
            insertlist(&alloc_head, tmp);
            return addr;
        }

        prev = cur;
        cur = cur->next;
    }

    return -1;
}

bool fusion(struct m_block *cur)
{
    struct m_block *next = cur->next;

    if (!next) {
        return false;
    }

    if (cur->addr + cur->size == next->addr) {
        printf("fusion cur addr %d size %d next size %d\n",
                cur->addr, cur->size, next->size);
        cur->size += next->size;
        cur->next = next->next;

        free(next);
        return true;
    }

    return false;
}

void fusion_free(void)
{
    struct m_block *cur = free_head.next;

    while (cur) {
        while (fusion(cur));
        cur = cur->next;
    }
}

/* 成功返回 true；失败返回 false，框架会自动输出 "error" */
bool MemPoolRelease(int startAddr)
{
    struct m_block *prev = &alloc_head, *cur = alloc_head.next;

    // 在此添加你的代码
    while (cur) {
        if (cur->addr == startAddr) {
            printf("free addr %d size %d\n", cur->addr, cur->size);
            // remove from alloc list
            prev->next = cur->next;

            // insert free list
            insertlist(&free_head, cur);

            fusion_free();
            return true;
        }

        prev = cur;
        cur = cur->next;
    }

    return false;
}

int main(void)
{
    MemPoolInit();

    int n;
    if (scanf("%d\n", &n) != 1)   { return -1; }

    char buf[BUF_LEN];
    for (int i = 0; i < n; i++) {
        if (fgets(buf, sizeof(buf), stdin) == NULL)   { return -1; }
        int info = atoi(buf + 8);
        if (buf[2] == 'Q') { // REQUEST
            int addr = MemPoolRequest(info);
            if (addr != -1) {
                (void)printf("%d\n", addr);
                printf("alloc addr %d size %d\n", addr, info);
            } else { (void)printf("error\n"); }
        } else { // RELEASE
            bool ret = MemPoolRelease(info);
            if (ret == false) { (void)printf("error\n"); }
        }
    }

    MemPoolDeinit();
    return 0;
}
