#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
        int key, key1;
        char buff[100];

        srand(time(NULL));

        key = rand();
        key1 = rand();

        printf("previous two keys: %d, %d\n", key, key1);

        key = rand();
        scanf("%s", buff);

        if (atoi(buff) == key)
                printf("success! Next key is %d\n", key);
        else
                printf("fail");

        return 0;
}