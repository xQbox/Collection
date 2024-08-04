#include <stdio.h>

int check_number(void) 
{   
    float c;    
    while (scanf("%f", &c) != 1 || c < 1)
    {
        printf("Wrong input\n");
        while(getchar() != '\n');   
    }
    return c;
} 


int main (void)
{   
    int res;
    res = check_number();
    printf("this is a number -> %d", res);
}