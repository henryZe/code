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



int main()
{
	Student *sthead = create_klist();
	//if()

	read_bit(sthead);

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
				write_bit(sthead);
				show_stulist(sthead);
				return 0;
				
		}
		
		while(getchar() != '\n');
	}
}


