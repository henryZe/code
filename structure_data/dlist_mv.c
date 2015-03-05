/*************************************************
 File name : dlist_mv.c
 Create date : 2013-11-06 23:39
 Modified date : 2013-11-06 23:39
 Author : henryZ
 Email : henryZ_e@163.com
 
 ***********************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef int elemType;

typedef struct node
{
	int    data;
	struct node *prev;
	struct node *next;
}listnode,*linklist;

linklist init_list(void)				//创建指针，无数据，指向本身
{
	linklist head = malloc(sizeof(listnode));
	head -> prev = head -> next = head;

	return head;
}

void add_list_tail(linklist new, linklist head)		//尾插法，传递的是整个指针
{
	new -> prev = head -> prev;
	new -> next = head;

	head-> prev = new;
	new -> prev -> next = new;
}

void show(linklist head)
{
	linklist p = head -> next;

	while(p != head)
	{
		printf("%d\t",p -> data);
		p = p -> next;
	}

	printf("\n");
}

void remove_node(linklist p)
{
	p -> prev -> next = p -> next;
	p -> next -> prev = p -> prev;

	p -> prev = p -> next = NULL;
}

void move_tail(linklist p,linklist head)
{
	remove_node(p);
	add_list_tail(p,head);
}

void rearrange(linklist head)
{
	linklist p = head -> prev;
	linklist save;
	int i =0;

	while(p != head)
	{
		if(p -> data %2 == 0 && i != 0)
		{
			move_tail(p,head);
			p = save;
		}

		else
		{
			save = p;
		}

		p = p -> prev;
		i++;
	}
}

void free_node(linklist head)
{
	linklist p = head;

	while(p != head)
	{
		free(p);
		p = p -> next;
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
		linklist new = malloc(sizeof(listnode));
		new -> data = i;

		add_list_tail(new,head);
	}
	
	show(head);

	rearrange(head);
	show(head);

	free_node(head);

	return 0;
}

