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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>



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


void show_stulist(Student *sthead)
{
	FILE file = NULL;
	file = open("student_list.txt","w");
	
	


	close(file);
}



bool write_bit(Student *sthead)
{
	FILE fd;
	fd = fopen("list_bit", "w",0644);
	
	if(fd == -1)
	{
		perror("fopen fail");
		return false;
	}

	Student *pos = NULL;
	int len = 0;
	
	list_for_each_entry(pos,&(sthead->list),list)
	{
		len = fwrite(pos,1,sizeof(Student),fd);

		if(len != sizeof(Student))
		{
			perror("fwrite error");	
			close(fd);

			return false;
		}
	}
	close(fd);

	return true;
}


bool read_bit(Student *sthead)
{
	int fd = open("list_bit",O_CREAT|O_RDWR,0644);

	if(fd == -1)
	{
		return false;
	}

	Student tmp;
	int  len = 0;

	while((len = read(fd,&tmp,sizeof(Student)))>0)
	{
		insert_klist(sthead,tmp.data);
	}

	close(fd);

	return true;
}

