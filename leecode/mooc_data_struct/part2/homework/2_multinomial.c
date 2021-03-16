#include <stdio.h>
#include <stdlib.h>

struct Gnode {
    int tag;	// 0 means data, 1 means subList
    union {
        int data;
        struct Gnode *subList;
    } uRegion;
    struct Gnode *next;
};

sum()
{

}

multiple()
{
    
}

int main(void)
{
    int num1, num2;

    scanf("%d", &num1);
    int *ratio1 = malloc(sizeof(int) * num1);
    for (int i = 0; i < num1; i++) {
        scanf("%d", ratio1 + i);
    }

    int *exponent1 = malloc(sizeof(int) * num1);
    for (int i = 0; i < num1; i++) {
        scanf("%d", exponent1 + i);
    }

    scanf("%d", &num2);
    int *ratio2 = malloc(sizeof(int) * num2);
    for (int i = 0; i < num2; i++) {
        scanf("%d", ratio2 + i);
    }

    int *exponent2 = malloc(sizeof(int) * num2);
    for (int i = 0; i < num2; i++) {
        scanf("%d", exponent2 + i);
    }

    for (int i = 0; i < num1; i++)
        printf("%d ", ratio1[i]);
    printf("\n");

    for (int i = 0; i < num1; i++)
        printf("%d ", exponent1[i]);
    printf("\n");

    for (int i = 0; i < num2; i++)
        printf("%d ", ratio2[i]);
    printf("\n");

    for (int i = 0; i < num2; i++)
        printf("%d ", exponent2[i]);
    printf("\n");

    return 0;
}
