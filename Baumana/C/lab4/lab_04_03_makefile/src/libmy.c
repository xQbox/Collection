#include <stdio.h>
#include "libmy.h"
#define SIZE 257
#define MAX_LEN_WORD 17


int check_smb(char n, char *line, int lvl)
{
    for(int i = 0 ; i < lvl; i++)
    {
        if ( n == line[i]) return 0;
    }
    return 1;
}
