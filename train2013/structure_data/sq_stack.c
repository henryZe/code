/*************************************************
 File name : sq_stack.c
 Created  date : 2013-11-05 15:55
 Modified date : 2013-11-05 15:55
 Author : heqingde
 E-mail : hqd173@163.com
 
 ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 10
typedef int elemType;

typedef struct Sqstack
{
	elemType data[SIZE];
	//表示栈顶
	int top;
}Sqstack;


//栈的创建
Sqstack* create_stack()
{
	Sqstack *stk = (Sqstack*)malloc(sizeof(Sqstack));
	if(stk == NULL)
	{
		perror("malloc fail:");
		exit(1);
	}

	stk->top = -1;
	return stk;
}

//入栈或压栈
bool push_stack(Sqstack *stk, elemType data)
{
	if(stk->top == (SIZE-1))
	{
		printf("full");
		return false;
	}
	stk->top++;
	stk->data[stk->top] = data;
	return true;
}

//出栈
bool pop_stack(Sqstack *stk, elemType *data)
{
	if(stk->top == -1)
	{
		printf("empty");
		return false;
	}

	*data = stk->data[stk->top];
	stk->top--;
	return true;
}
//显示
void show_stack(Sqstack *stk)
{

/*	int i = 0;
	for(i=0; i<=stk->top; i++)
	{	
		printf("%d\t", stk->data[i]);
	}

	printf("\n");
*/
	elemType data;
	
	while(pop_stack(stk, &data))	
	{
		printf("%d", data);
	}
	printf("\n");

}

int main()
{
	Sqstack *head=create_stack();
	if(head == NULL)
	{
		printf("create fail\n");
		return 0;
	}

/*	int i;
	int num;

	printf("input number:");
	for(i=0;i<SIZE;i++)
	{
		scanf("%d",&num);
		push_stack(head,num);
	}

	printf("The stack:");
	show_stack(head);
*/
	int num;
	int res=0;

	printf("input num:");
	scanf("%d",&num);

	while((num/2)!=0)
	{
		res = num % 2;
		push_stack(head,res);
		num = num / 2;
	}
	push_stack(head,num);

	printf("The result:");
	show_stack(head);

	return 0;
}

