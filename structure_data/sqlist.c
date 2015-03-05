#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20
typedef int elemType;

typedef struct sqlist
{
	elemType data[SIZE];
	int length;
}sqlist;

//create order list
sqlist* create_list()
{
	sqlist *sq = (sqlist*)malloc(sizeof(sqlist));
	if(sq != NULL)
	{
		sq->length = -1;
		return sq;
	}
	return NULL;
}


bool insert_list_pos(sqlist *sq, int pos, elemType data)
{
	if(sq->length == (SIZE-1))
	{
		printf("is full!\n");
		return false;
	}

	sq->length++;
	
	int len;

//	if(pos>sq->length)
//		length=pos;					//防止pos大于length的情况

	for(len=sq->length;len>(sq->length-pos);len--)
	{
		sq->data[len]=sq->data[len-1];
	}

	sq->data[sq->length-pos+1]=data;
	
	return true;
}

//insert data
bool insert_list(sqlist *sq, elemType data)
{
	if(sq->length == (SIZE-1))
	{
		printf("is full\n");
		return false;
	}
	
	sq->length++;
	sq->data[sq->length] = data;
	return true;
}

//delete data
bool delete_list(sqlist *sq, elemType data)
{
	int len = sq->length;
	while(len != -1)
	{
		if(sq->data[len] == data) break;
		len--;
	}
	
	if(len == -1)return false;
	
	for(; len<sq->length; len++)
	{
		sq->data[len] = sq->data[len+1];
	}
	sq->length--;
	return true;
}

//show data
void show_list(sqlist *sq)
{
	int len = sq->length;

	while(sq->length != -1)
	{
		printf("%d\t", sq->data[sq->length]);
		sq->length--;
	}
	sq->length = len;
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
	sqlist *sq = create_list();
	if(sq == NULL)
	{
		printf("create fail!\n");
		return 0;
	}
	
	int i = 0;
	for(i=0; i<5; i++)
	{
		if(insert_list(sq, get_random(20)))continue;
		else
			break;
	}
	
	show_list(sq);

	int M;
	int pos;

	printf("please input insert data:");
	scanf("%d",&M);

	printf("please input the position:");
	scanf("%d",&pos);

	insert_list_pos(sq,pos,M);
	show_list(sq);

	int N=0;
	printf("please input delete data:");
	scanf("%d", &N);
	
	delete_list(sq, N);
	show_list(sq);

	free(sq);
	return 0;
}



