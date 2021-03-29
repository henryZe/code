/*************************************************
 File name : linksqueue.c
 Created  date : 2013-11-06 15:55
 Modified date : 2013-11-06 15:55
 Author : heqingde
 E-mail : hqd173@163.com
 
 ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef int elemType;

typedef struct squeue
{
	elemType data;
	struct squeue *next;
}squeue;

typedef struct linksqu
{
	squeue *rear;
	squeue *front;
}linksqu;

linksqu* create_linksq()
{
	linksqu *lsqu = (linksqu*)malloc(sizeof(linksqu));
	if(lsqu == NULL)
	{
		exit(1);
	}

	lsqu->rear = NULL;
	lsqu->front = NULL;
	return lsqu;
}

bool insert_linksq(linksqu *lsqu, elemType data)
{
	squeue *new = (squeue*)	malloc(sizeof(squeue));
	if(new == NULL)
	{
		return false;
	}

	new->data = data;
	new->next = NULL;

	if(lsqu->rear == NULL && lsqu->front == NULL)
	{
		lsqu->rear = lsqu->front = new;
		return true;
	}
	
	lsqu->rear->next = new;
	lsqu->rear = new;
	return true;	
}

bool export_linksq(linksqu *lsqu, elemType *data)
{
	if(lsqu->front == NULL)
	{
		return false;
	}

	*data = lsqu->front->data;
	squeue *p = lsqu->front;
	lsqu->front = p->next;
	free(p);
	return true;
}

int main()
{
	linksqu *lsqu = create_linksq();
	int i;

	for(i=0; i<7; i++)
	{
		insert_linksq(lsqu, i);
	}

	int data = 0;
	while(export_linksq(lsqu, &data))
	{
		printf("%d\t", data);
	}

	printf("\n");
	return 0;
}

