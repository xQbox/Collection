#include <stdio.h>
#include <string.h>
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

void check_the_line(char *line, int top)
{
    int i = 0;
    int p = 0; 
    while((line[i] != '+') && (i < top)) // add maximum
    { 
        if(line[i] == ' ') p++; 
        i++; 
    }
    if (i == p)
    {
        int dif = i;
        int ch = 0;
        while((line[i] != '(') && (i < top))
        {
            if ((line[i] >= '0') && (line[i] <= '9')) ch++;
            i++;
        }
        dif = i - dif;
        if (((dif - 1) == ch) && line[i] == '(' && ch > 0)
        {
            sep_test(line, i, top);
        }
        else
        {
            printf("NO");
        }
    }
    else 
    {
        printf("NO");
    }
}


void check_the_number(char *line, int top)
{
    int i = 0;
    int p = 0; 
    while((line[i] != '(') && (i < top)) // add maximum
    {
        if(line[i] == ' ') p++; 
        i++;
    }
    if (i == p)
    {
        sep_test(line, i, top);
    }
    else 
    {
        printf("NO");
    }
}


void sep_test(char *line, int i, int top)
{
    int dif = i;
    int p = 0;
    while((line[i] != ')') && (i < top)) // add maximum
    {
        if (line[i] >= '0' && line[i] <= '9') p++;
        i++;
    }
    dif = (i - 1) - dif;
    if ((p == 3) && (dif == 3))
    {
        digit_test(line, i, top);
    }
    else 
    {
        printf("NO");
    }
}

void digit_test(char *line, int i, int top)
{
    i = i + 1;
    if (line[i] == '-')
    {
        int dif = i;
        int p = 0;
        i = i + 1;
        while((line[i] != '-') && (i < top))
        {
            if (line[i] >= '0' && line[i] <= '9') p++;
            i++;
        }
        dif = (i - 1) - dif;
        if ((p == 3) && (dif == 3))
        {
            digit_test_two(line, i, top);
        }
        else
        {
            printf("NO");
        }
    }

    else 
    {
        printf("NO");
    }
}

void digit_test_two(char *line, int i , int top)
{
    int dif = i;
    i = i + 1;
    int p = 0;
    while((line[i] != '-') && (i < top))
    {
        if (line[i] >= '0' && line[i] <= '9') p++;
        i++;
    }
    dif = (i - 1) - dif;
    if ((p == 2) && (dif == 2))
    {
        digit_last(line, i, top);
    }
    else
    {
        printf("NO");
    }   
}


void digit_last(char *line, int i, int top)
{
    int dif = i;
    int place = 0;
    i = i + 1;
    int p = 0;
    while((line[i] != '\0') && (i < top))
    {
        if (line[i] >= '0' && line[i] <= '9') p++;
        if ((p == 2) && (line[i] == ' ')) place++; 
        i++;
    }
    dif = (i - 1) - dif;
    if ((p == 2) && (place == dif - 3))
    {
        printf("YES");
    }
    else
    {
        printf("NO");
    }   
}
