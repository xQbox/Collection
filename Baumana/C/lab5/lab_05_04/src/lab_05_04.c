#include <stdio.h>
// #include "libmy.h"
#include <string.h>
#include <stdlib.h>
#define ERROR_Less_Arguments 1

int main()

{
    int top = 0;
    char ch;
    char N[30];
    printf("Введите символы. конец ввода - 0\n");
    while ((ch = getchar()) != '0')
    
    {

        N[top] = ch; 
        top += 1;
    
    }

    N[top] = '\0';
    printf("%s", N);
    char *a = "AAAAAAA";
    char *b = "AAAAAA";
    if (b > a) 
    {
        printf("OKEY");
    }
    return 0;
}
