#include <stdio.h>
#include <string.h>
#include "libmy.h"
#define WRONG_PARAMETRS -1
#define TOO_LONG_WORD -2
#define NO_SUCH_DIRECTORY -3
int check_param();
int maxim();


int main(int argc, char **argv)
{
    if (!check_param(argc, argv))
    {
        FILE *f;
        f = fopen(argv[1], "r");

        if (f == NULL)

        {
            printf("No_such_directory\n");
            
            return NO_SUCH_DIRECTORY;
        }

        int pos = 2;
        float max, sec_max; 
        float res = maxim(f, &max, &pos, &sec_max);

        
        printf(" POS -> %d MAX -> %f RES -> %f \n", pos, max, res);
        rewind(f);
        summa(f, &max, &sec_max);
    }

    printf("PASS\n");

    
    return 0;

}


// int check_param(int argc, char **argv)
// {
//     if (argc != 2)
    
//     {  
//         printf("ERROR, no input parametrs\n");
//         return WRONG_PARAMETRS;
//     }
//     if(strlen(argv[1]) > 127) 
//     {   
//         printf("ERROR, too long input\n");
//         return TOO_LONG_WORD;
//     }

//     return 0;
// }


// int max();

