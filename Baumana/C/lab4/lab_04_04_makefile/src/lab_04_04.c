#include <stdio.h>
#include <string.h>
#include "libmy.h"
#define SIZE 257
#define MAX_WORD_LEN 17 
void check_the_line();
void check_the_number();
void sep_test();
void digit_test();
void digit_test_two();
void digit_last();


int main(void)
{
    char S[SIZE];
    int flag = 0;
    printf("Input string: ");
    fgets(S, SIZE, stdin);
    for(size_t i = 0; i < strlen(S); i++)
    {
        if (S[i] == '+') flag = 1; 
    }
    if (flag)
    {
        check_the_line(S, (int) strlen(S));
    }
    else 
    {
        check_the_number(S, (int) strlen(S));
    }
    return 0;
}
