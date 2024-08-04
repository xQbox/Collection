#include <stdio.h>
#include "libmy.h"

#define SIZE 257
#define MAX_LEN_WORD 17

void ask_stroka(char *line, int N, int M);
int check_smb(char N);
int check_line(char *exp, char S[SIZE / 2][MAX_LEN_WORD], int top);
int len(char *line);



int main(void)
{
    char A[2][SIZE];
    ask_stroka(A[0], SIZE, 2); // Инициализация массива строк
    
    char S[SIZE / 2][MAX_LEN_WORD];
    int n , m, top;
    n = m = 0; 
    for (int i = 0; i < 2;i++)
    {

        for(int k = 0; A[i][k] != '\0'; k++)
        {
            if(check_smb(A[i][k]))
            {
                S[n][m] = A[i][k];
                m ++;
            }
            else
            {
                if (m > 0)
                {
                    S[n][m] = '\0';
                    n++;
                    m = 0;
                }
            }
        }
        if(m > 0)
        {
            S[n][m] = '\0';
            n++; 
            m = 0;
        }
        top = n;
    }

    int sum = -1;
    for(int i = 0; i < top; i++)
    {
        char *line = S[i];
        sum = check_line(line, S, top);
        if (sum == 0)
        {
            printf("\n%s\n", line);
        }
    }

}

