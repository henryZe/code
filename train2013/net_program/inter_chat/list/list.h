#ifndef  __LIST_H__
#define  __LIST_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct node
{
	void   *dat;
	struct node  *prev,*next;
	int    size;
};

//创建一个链表头
struct node *list_create(int size);
int    list_addtail(struct node *head,void *dat);
int    list_addhead(struct node *head,void *dat);
void   list_destroy(struct node *head);
//用户登录查找
struct node *list_find(struct node *head,void *dat,int (*cmp)(void *dat1,void *dat2));
//用户注销
int list_del(struct node *head,void *dat,int (*cmp)(void *dat1,void *dat2));

#endif
