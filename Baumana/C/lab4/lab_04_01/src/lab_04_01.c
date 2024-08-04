#include <stdio.h>
#include <string.h>
#define SIZE 257


int ask_stroka(char *N, int n);
void my_strrchar();



int main()
{
    char stroka [2][SIZE];      
    char Arr[2][16][16];
    for (int i =0; i< 2; i++)
    {
        ask_stroka(&stroka[i][0], SIZE);
    }
    for (int i = 0; i< 2 ; i++)
    {
        int pointer = 0;
        for (int k = 0; stroka[0][k] != '\0'; k++)
        {
            if (stroka[i][k] == ' ')
            {
                Arrc[i][pointer] = '\0';
                pointer += 1;
                pointer = 0;
            }
            else
            {
                Arr[i][pointer] = stroka[i][k];
                pointer += 1;
            }
        } 
        Arr[i][pointer] = '\0';
    }
    
    int num_rows = sizeof(Arr) / sizeof(Arr[0]);
    int num_cols = sizeof(Arr[0]) / sizeof(Arr[0][0]);

    for (int i = 0; i < num_rows; i++) 
    {
        for (int j = 0; j < num_cols; j++) 
        {
            printf("%s ", Arr[i][j]);
        }
        printf("\n");
    }
}

int ask_stroka(char *N, int n)
{
    int res = 0;
    int i = 0;
    int buf = 0;
    while(res != EOF && res !='\n')
    {
        res = getchar();

        if (res == '\n') break;
        
        if (i < n - 1)
        {   
            buf += 1;
            *(N + i) = res;
            if (*(N + i) == ' ') buf = 0;
            if (buf > 16)
            {
                *(N + i) = ' ';
                buf = 0;
            }
            i += 1;
            
        }
    }

    *(N + i) = '\0';
    return i;
}

