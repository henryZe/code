/*************************************************
 File name : klist_lin.c
 Create date : 2013-11-07 00:49
 Modified date : 2013-11-07 00:49
 Author : henryZ
 Email : henryZ_e@163.com
 
 ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "kernel_list.h"

typedef struct node
{
	int data;

	struct list_head list;
}*linklist,linknode;


linklist init_list(void)
{
	linklist head = malloc(sizeof(linknode));
	
	INIT_LIST_HEAD(&head -> list);

	return head;
}

void show(linklist head)
{
	struct list_head *pos;
	linklist p;

	list_for_each(pos,&head -> list)
	{
		p = list_entry(pos,linknode,list);

		printf("%d\t",p ->data);
	}

	printf("\n");
}

void rearrange(linklist head)
{
	struct list_head *pos;
	struct list_head *save;
	linklist p;
	int i = 0;

	list_for_each_prev(pos, &head -> list)
	{
		p = list_entry(pos, linknode, list);

		if(p -> data %2 == 0 && i != 0)
		{
			list_move_tail(pos,&head -> list);
			pos = save;
		}
		else
		{
			save = pos;
		}
		i++;
	}
}



int main(void)
{
	linklist head;

	head = init_list();

	int n,i;
	scanf("%d",&n);

	for(i=1;i<=n;i++)
	{
		linklist new = malloc(sizeof(linknode));
		new ->data = i;

		list_add_tail(&new -> list, &head -> list);
	}

	show(head);

	rearrange(head);
	show(head);

	return 0;
}
	
