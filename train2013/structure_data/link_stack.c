/*************************************************
 File name : link_stack.c
 Created  date : 2013-11-05 15:55
 Modified date : 2013-11-05 17:11
 Author : heqingde
 E-mail : hqd173@163.com
 
 ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 30

typedef int  elemType;

typedef struct Lstack
{
	elemType data;
	struct Lstack *next;
}Lstack;


//栈的创建
Lstack* create_stack()
{
	Lstack *stk = (Lstack*)malloc(sizeof(Lstack));
	if(stk == NULL)
	{
		perror("malloc fail:");
		exit(1);
	}

	stk->next = NULL;
	return stk;
}

//入栈或压栈
bool push_stack(Lstack *stk, elemType data)
{
	Lstack* new  = (Lstack *)malloc(sizeof(Lstack));
	//if()
	new->data = data;
	new->next = NULL;

	new->next = stk->next;
	stk->next = new;
	return true;
}

//出栈
bool pop_stack(Lstack *stk, elemType *data)
{
	if(stk->next == NULL)
	{
		printf("\n******** End *********");
		return false;
	}

	Lstack *p = stk->next;
	stk->next = p->next;
	*data = p->data;
	free(p);

	return true;
}
//显示
void show_stack(Lstack *stk)
{
	elemType data;
	
	while(pop_stack(stk, &data))	
	{
		printf("%x", data);
	}
	printf("\n");
}


int main()
{
	Lstack *stk = create_stack();
	
	while(1)
	{
		int  num;
		int  mode;
		int  res=0;

		printf("input num:");
		scanf("%d",&num);

		printf("input mode:");
		scanf("%d",&mode);

		while((num/mode)!=0)
		{
			res = num % mode;
			push_stack(stk,res);
			num = num / mode;
		}
		push_stack(stk,num);

		printf("The translated %d number is ",mode);
		show_stack(stk);

		printf("\n");
	}

	return 0;
}

