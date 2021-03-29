/*************************************************
 File name : kernel_list.c
 Created  date : 2013-11-05 14:35
 Modified date : 2013-11-05 14:35
 Author : heqingde
 E-mail : hqd173@163.com
 
 ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "kernel_list.h"


typedef struct student
{
	int age;
	float height;
	char sex;
	char name[31];
}student;


typedef student elemType;

typedef struct Student
{
	elemType data;
	struct list_head list;
}Student;



Student* create_klist()
{
	Student *sthead = (Student*)malloc(sizeof(Student));
	//if()
	INIT_LIST_HEAD(&(sthead->list));

	return sthead;
}


bool insert_klist(Student *sthead, elemType data)
{	
	Student *new = (Student*)malloc(sizeof(Student));
	//if()
	new->data = data;
	INIT_LIST_HEAD(&(new->list));

	list_add_tail(&(new->list), &(sthead->list));

	return true;
}


bool delete_klist(Student *sthead,elemType data)
{
	Student *pos = NULL;

	list_for_each_entry(pos,&(sthead->list),list)
	{
		if(strcmp(pos->data.name,data.name)==0)
		{
			list_del(&(pos->list));
			free(pos);

			break;
		}
	}
	return true;
}


void dellist(Student *sthead)
{
	student stu = {.age=0, .height=0, .sex='0'};

	printf("delete name:");
	scanf("%s",stu.name);

	delete_klist(sthead, stu);
}


void show_klist(Student *sthead)
{
	struct list_head *head = &(sthead->list);
	Student *pos = NULL;

	list_for_each_entry(pos, head, list)
	{
		printf("名字%s:身高%.2fcm:年龄%d:性别%c\n", pos->data.name,pos->data.height,pos->data.age,pos->data.sex);
	}

	printf("\n");
}


void insert_function(Student *sthead)
{
	int  age,height;
	char sex;
	char name[31];

	printf("Input the age:");
	scanf("%d",&age);

	printf("Input the sex:");
	scanf("\n%c",&sex);

	printf("Input the height:");
	scanf("%d",&height);

	printf("Input the name:");
	scanf("\n%s",name);

	student st;
	st.age=age;
	st.height=height;
	st.sex=sex;
	strcpy(st.name,name);

	insert_klist(sthead,st);
}

int main()
{
	Student *sthead = create_klist();
	//if()

	while(1)
	{	
		char func;
		printf("********************************\n");
		printf("a-添加\tl-显示\nd-删除\tq-退出\n");
		func=getchar();

		switch(func)
		{
			case 'a':
				insert_function(sthead);
				break;

			case 'l':
				show_klist(sthead);
				break;

			case 'd':
				dellist(sthead);
				break;

			case 'q':
				return 0;
		}
		
		while(getchar() != '\n');
	}
}


