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

#define LENGTH 10

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
		head->next = head;
		return head;
	}
	return NULL;
}

bool insert_list(Linklist *head, elemType data)
{
	Linklist *new = (Linklist*)malloc(sizeof(Linklist));
	
	if(new == NULL) 
		return false;

	new->data = data;
	new->next = new;

	Linklist *p = head;
	while(p->next != head)
	{
		p = p->next;
	}

	new->next = p->next;		//指向head
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
	while(p->next->data!=data && p->next->next != head)
	{
		p=p->next;
	}

	if(p->next->data!=data && p->next->next == head)
	{
		return false;
	}

	Linklist *del=p->next;	
	p->next=p->next->next;
	
	free(del);

	return true;
}


void show_list(Linklist *head)
{
	Linklist *p=head;

	while(p->next != head)
	{
		p = p->next;
		printf("%d\t", p->data);
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


bool delete_list_next(Linklist *p)
{
	Linklist *del=p->next;
	p->next=p->next->next;

	free(del);
	return true;
}


Linklist* lucky_del(Linklist *head, int L)
{
	Linklist *p = head;
	
	int  i;

	while(p->next!=p)
	{
		for(i=1;i<L;i++)
		{
			p=p->next;
		}
		delete_list_next(p);
	}
	return p;	
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
		insert_list(head,i);// get_random(100));
	}

	printf("********show insert********\n");
	show_list(head);


/*	printf("please input delete data:");
	int N = 0;
	scanf("%d", &N);
	delete_list(head, N);
	show_list(head);

	printf("please input insert data:");
	int M=0;
	scanf("%d",&M);
	insert_list(head, M);		
	show_list(head);
*/

	printf("Enter lucky number:");
	int L = 0;
	scanf("%d",&L);
	
	Linklist *poi=NULL;
	poi=lucky_del(head,L);
	printf("the lucky is %d.\n",poi->data);

	free(poi);	

/*	Linklist *p = head;
	Linklist *q = head;

	do
	{
		free(p);
		p = p->next;
	}while( p != q );
*/
	return 0;
}


