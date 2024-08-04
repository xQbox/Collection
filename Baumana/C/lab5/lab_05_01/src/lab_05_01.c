#include <stdio.h>
#include "libmy.h"
#define NO_DATA -1
#define NO_CIFRA -2
#define TOO_LONG_INT -3
int process();


int main(void)
{
    FILE *f;
    int f_max;
    int s_max;

    f = fopen("ex_1.txt", "w");

    if (process(f, &f_max, &s_max) == 0)

    {
        printf("First max is %d\n", f_max);
        printf("Second max is %d\n", s_max);
    }

    else

    {
        return NO_DATA;
    }

    fclose(f);
    return 0;
}


// int process(FILE *f, int *f_max, int *s_max)
// {   
//     int smb;

//     printf("Input numbers: ");
//     while(scanf("%d", &smb) == 1)
    
//     {
//         if (smb == -1) 

//         {
//             printf("Wrong input\n");
//             return TOO_LONG_INT;
//         }

//         fprintf(f, "%4d", smb);
    
//     }

//     fclose(f);

//     int num;
//     int res = 0;
    
//     f = fopen("ex_1.txt", "r");
    
//     if(fscanf(f, "%d", f_max) == 1)
    
//     {   
//         res+=1;     
    
//         while(fscanf(f, "%d", &num) == 1)
    
//         {
//             res+=1;
    
//             if (num >= *f_max)
    
//             {
//                 *s_max = *f_max;
//                 *f_max = num;
//             }
    
//             else if (num >= *s_max)
    
//             {
//                 *s_max = num;
//             }
    
//         }
    
//         if(res > 2)
    
//         {
//             return 0;
//         }
    
//         else
    
//         { 
//             printf("Error, not enough data: no second digit\n");
//             return NO_CIFRA;
//         }
    
//     }

//     printf("Error, no input data \n");
//     return NO_DATA;
// }
