/*************************************************
 File name : dlist.c
 Created  date : 2013-11-04 17:27
 Modified date : 2013-11-04 17:27
 Author : heqingde
 E-mail : hqd173@163.com
 
 ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define  LENGTH  10

typedef int elemType ;

typedef struct Dlist
{
	elemType data;
	struct Dlist *prior;
	struct Dlist *next;
}Dlist;


//init create
Dlist* create_dlist()
{
	Dlist *dhead = (Dlist*)malloc(sizeof(Dlist));
	//
	dhead->prior = NULL;
	dhead->next = NULL;

	if(dhead != NULL)
	{
		dhead -> prior = dhead;
		dhead -> next  = dhead;
	
		return dhead;
	}
	return NULL;
}

//insert  尾插法插入数据 
Dlist* insert_dlist(Dlist *dhead, elemType data)
{
	Dlist  *new = (Dlist*)malloc(sizeof(Dlist));

	if(new == NULL)
		return false;

	new -> data = data;
	new -> next = new;
	new -> prior= new;

	Dlist *p = dhead;
	while(p -> next != dhead)
	{
		p = p -> next;
	}

	new -> next = p -> next;
	p -> next -> prior = new;

	p -> next = new;
	new -> prior = p;

	return dhead;
}

//show 正反顺序显示链表里面的数据
void show_dlist(Dlist *dhead)
{
	Dlist *p = dhead;

	while(p -> next != dhead)			//正序显示
	{
		p = p -> next;
		printf("%d\t",p -> data);
	}

	printf("\n");

/*	p = dhead;

	while(p->prior != dhead)
	{
		p = p -> prior;
		printf("%d\t",p -> data);		//反序显示
	}

	printf("\n");
*/
}

void delete_dlist(Dlist *p)
{
	p -> prior -> next = p -> next;
	p -> next -> prior = p -> prior;

	p -> next = NULL;
	p -> prior= NULL;

	free(p);
}



void change_dlist(Dlist *dhead)
{
	Dlist *p = dhead -> prior;
	Dlist *save = NULL;
	int   i  = 0;

	elemType data;

	while(p != dhead)
	{
		if(((p -> data) %2) ==0 && i != 0)
		{
			data = p->data;

			delete_dlist(p);
			insert_dlist(dhead,data);
			p = save;
		}

		else
		{
			save = p;
		}
		
		i++;
		p = p -> prior;
	}
}




int main()
{
	Dlist *dhead = create_dlist();
	if(dhead == NULL)
	{
		printf("create fail\n");
		return 0;
	}

	int i;
	for( i=1; i<LENGTH; i++)
	{
		insert_dlist(dhead,i);
	}

	printf("******** show insert ********\n");
	show_dlist(dhead);


	change_dlist(dhead);
	
	printf("******** show insert ********\n");
	show_dlist(dhead);



	Dlist *p = dhead;				//free
	Dlist *q = dhead;

	do
	{
		free(p);
		p = p -> next;
	}while(p != q);

	return 0;
}



