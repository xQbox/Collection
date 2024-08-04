#include <stdio.h>
// #include <libmy.h>

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

        for(int k =0 ; A[i][k] != '\0'; k++)
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
        printf("Input string: ");
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
