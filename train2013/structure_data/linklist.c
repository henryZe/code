/*************************************************
 File name : linklist.c
 Created  date : 2013-11-04 14:26
 Modified date : 2013-11-04 14:26
 Author : heqingde
 E-mail : hqd173@163.com
 
 ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LENGTH 6

typedef int elemType;

typedef struct Linklist
{
	elemType  data;
	struct    Linklist* next;
}Linklist;


Linklist* create_list()
{
	Linklist *head = (Linklist*)malloc(sizeof(Linklist));
	if(head != NULL)
	{
		head->next = NULL;
		return head;
	}
	return NULL;
}

bool insert_list(Linklist *head, elemType data)
{
	Linklist *new = (Linklist*)malloc(sizeof(Linklist));
	if(new == NULL) return false;
	new->data = data;
	new->next = NULL;

	Linklist *p = head;
	while(p->next != NULL)
	{
		p = p->next;
	}

	p->next = new;
	return true;
}


/*Linklist* delete_list(Linklist *head, elemType data)
{
	Linklist *p = head;
	while(p->data != data && p->next != NULL)
	{
		p = p->next;
	}

	if(p->next == NULL && p->data != data) return head;

	Linklist *q = head;
	while(q->next != p)
	{
		q = q->next;
	}

	q->next = p->next;
	free(p);
	return head;
}
*/
bool  delete_list(Linklist *head,elemType data)
{
	Linklist *p = head;
	while(p->next->data!=data && p->next->next != NULL)
	{
		p=p->next;
	}

	if(p->next->data!=data && p->next->next == NULL)
	{
		return false;
	}

	Linklist *del=p->next;	
	p->next=p->next->next;
	
	free(del);

	return true;
}


Linklist* invert_list(Linklist *head)
{	
	Linklist *pList  = head->next;
	Linklist *paPre  = NULL;
	Linklist *paNext = NULL;		//运用指针,而不是malloc,以防释放后丢失数据
	
	do
	{
		paNext=pList->next;
		pList->next=paPre;
		paPre=pList;
		pList=paNext;
	}while(pList!=NULL);
	
	head->next=paPre;

	return  head;
}


void show_list(Linklist *head)
{
	head=head->next;

	while(head != NULL)
	{
		printf("%d\t", head->data);
		head = head->next;
	}

	printf("\n");
}

int get_random(int mode)
{
	struct timeval now;
	gettimeofday(&now, NULL);
	srandom(now.tv_usec);

	return random()%mode;
}

int main()
{
	Linklist *head = create_list();
	if(head == NULL)
	{
		printf("create fail\n");
		return 0;
	}

	int i = 0;
	for(i=0; i<LENGTH; i++)
	{
		insert_list(head, get_random(100));
	}

	printf("********show insert********\n");
	show_list(head);

	printf("********invert data********\n");
	show_list(invert_list(head));

	printf("please input delete data:");
	int N = 0;
	scanf("%d", &N);
	delete_list(head, N);
	show_list(head);

	printf("please input insert data:");
	int M=0;
	scanf("%d",&M);
	insert_list(head, M);		
	show_list(head);

	Linklist *p = head;
	while(p != NULL)
	{
		p=head->next;
		free(head);
		head = p;
	}
	return 0;
}


