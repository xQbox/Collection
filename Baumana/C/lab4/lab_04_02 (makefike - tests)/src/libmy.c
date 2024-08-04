#include <stdio.h>
#include "libmy.h"
#define SIZE 257
#define MAX_LEN_WORD 17



int check_smb(char N)
{
    if (((int) N > 64 && ((int) N < 91)) || (((int) N > 96) && ((int) N < 123)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


void ask_stroka(char *s, int N, int M)
{   
    
    int i = 0;
    for (int k = 0; k < M; k++)
    {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            if (i < N - 1)
            {
                *(s + k * SIZE + i) = ch;
                i += 1;
            }
        *(s + SIZE * k + i) = '\0';
        i = 0;  
    }
}


int check_line(char *line, char S[SIZE / 2][MAX_LEN_WORD], int top)
{
    int res = 0;
    int comp = 0;
    for(int i = 0; i < top; i++)
    {
        if(len(line) == len(S[i]))
        {
            for(int k = 0; S[i][k] != '\0'; k++)
            {
                if(line[k] == S[i][k])
                {
                    comp += 1;
                }
            }
            if (comp == len(line)) res ++;
        }
        comp = 0;
    }
    if (res > 1) return 1;
    return 0;
}


int len(char *line)
{
    int top = 0;
    for(int i = 0;line[i] != '\0'; i++)
    {
        top += 1;
    }
    return top;
}
