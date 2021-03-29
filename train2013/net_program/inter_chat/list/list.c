#include "list.h"

struct node *list_create(int size)
{
	struct node *head = NULL;

	head = malloc(sizeof(*head));
	if(head == NULL)
	{
		perror("malloc");
		return NULL;
	}

	head->dat = NULL;
	head->next = head->prev = head;
	head->size = size;

	return head;
}

int list_addtail(struct node *head,void *dat)
{
	struct node *new = NULL;

	new = malloc(sizeof(*new));
	if(new == NULL)
	{
		perror("malloc");
		return -1;
	}

	new->dat = malloc(head->size);
	if(new->dat == NULL)
	{
		perror("malloc");
		return -1;
	}

	new->size = head->size;
	memcpy(new->dat,dat,new->size);

	//把节点插入到链表尾
	new->next = head;
	new->prev = head->prev;
	
	head->prev->next = new;
	head->prev = new;

	return 0;
}


//头插法
int list_addhead(struct node *head,void *dat)
{
	struct node *new = NULL;

	new = malloc(sizeof(*new));
	if(new == NULL)
	{
		perror("malloc");
		return -1;
	}

	new->size = head->size;
	memcpy(new->dat,dat,new->size);

	//把节点插入到链表头
	new->prev = head;
	new->next = head->next;

	head->next = new;
	head->next->prev = new;

	return 0;
}


void list_destroy(struct node *head)
{
	struct node *tmp,*next;

	for(tmp = head->next; tmp != head; tmp = next)
	{
		next = tmp->next;
		free(tmp->dat);
		free(tmp);
	}

	free(head);
}


struct node *list_find(struct node *head,void *dat,int (*cmp)(void *dat1,void *dat2))
{
	struct node *tmp;

	for(tmp = head->next; tmp != head; tmp = tmp->next)
	{
		if(cmp(tmp->dat,dat) == 0)
		{
			return tmp; 
		}
	}

	return NULL;
}


int list_del(struct node *head, void *dat, int (*cmp)(void *dat1,void *dat2))
{
	struct node *tmp;

	for(tmp = head->next; tmp != head; tmp = tmp->next)
	{
		if(cmp(tmp->dat,dat) == 0)
		{
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;

			free(tmp->dat);
			free(tmp);

			return 0;
		}
	}

	return -1;
}
