/*************************************************
 File name : sq_queue.c
 Created  date : 2013-11-06 14:43
 Modified date : 2013-11-06 14:43
 Author : heqingde
 E-mail : hqd173@163.com
 
 ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 7

typedef int elemType;

typedef struct Squeue
{
	elemType data[SIZE];
	int rear, front;
}Squeue;


Squeue* create_queue()
{
	Squeue *squ = (Squeue*)malloc(sizeof(Squeue));
	if(squ == NULL)
	{
		exit(1);
	}
	squ->rear = 1;
	squ->front = 1;
	return squ;
}

bool insert_queue(Squeue *squ, elemType data)
{
	if((squ->rear+1)%SIZE == squ->front)
	{
		printf("is full\n");
		return false;
	}
	squ->data[squ->rear] = data;
	squ->rear = (squ->rear+1)%SIZE;
	return true;
}

bool export_queue(Squeue *squ,  elemType *data)
{
	if(squ->front == squ->rear)
	{
		printf("empty\n");
		return false;
	}

	*data = squ->data[squ->front];
	squ->front = (squ->front+1)%SIZE;
	return true;
}

int main()
{
	Squeue *squ = create_queue();

	int i=0; 
	for(i=1; i<8; i++)
	{
		insert_queue(squ, i);
	}

	int data = 0;
	while(export_queue(squ, &data))
	{
		printf("%d\t", data);
	}
	printf("\n");
	return 0;
}

