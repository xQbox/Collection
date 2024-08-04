#include <stdio.h>
#include <string.h>
#define SIZE 257
#define MAX_LEN_WORD 17
int check_smb(char n, char *line, int lvl);



int main(void)
{
    char S[SIZE]; 
    fgets(S, SIZE, stdin);
    char line[SIZE / 2][MAX_LEN_WORD];
    char sep[] = "!?.:;,- ";
    char *space_string = strtok(S, sep);
    int k , p;
    k = p = 0;
    while(space_string != NULL)
    {
        for(int i = 0; *(space_string + i) != '\0'; i++)
        {
            line[k][p] = *(space_string + i);
            p++; 
        }
        space_string = strtok(NULL,sep);
        line[k][p] = '\0';
        p = 0;
        k++;
    }

    char stroka[SIZE];
    int lvl = 0;
    for(int i = k - 2; i > -1; i--)
    {
        char M[MAX_LEN_WORD];
        int top = 0;
        for(int p = 0; line[i][p] != '\0'; p++)
        {   
            if (check_smb(line[i][p], M, top))
            {   
                stroka[lvl] = line[i][p];
                M[top] = line[i][p];
                lvl += 1;
                top += 1;
            }
        }
        if (i > 0)
        {
            stroka[lvl] = ' ';
            lvl += 1;
        }
    }
    stroka[lvl] = '\0';
    printf("Result %s\n", stroka);
    return 0;
}


int check_smb(char n, char *line, int lvl)
{
    for(int i = 0 ; i < lvl; i++)
    {
        if ( n == line[i]) return 0;
    }
    return 1;
}
