#include <stdio.h>
#include <string.h>
#include "libmy.h"
#define WRONG_PARAMETRS -1
#define TOO_LONG_WORD -2
#define NO_SUCH_DIRECTORY -3


int check_param(int argc, char **argv)
{
    if (argc != 2)
    
    {  
        printf("ERROR, no input parametrs\n");
        return WRONG_PARAMETRS;
    }
    if(strlen(argv[1]) > 127) 
    {   
        printf("ERROR, too long input\n");
        return TOO_LONG_WORD;
    }

    return 0;

}

int maxim(FILE *f , float *max, int *pos, float *sec_max)
{
    float num;
    float res = 0.;
    int place = 0;
    int dif = 0;
    if (fscanf(f, "%f", max) == 1)
    {

        res += *max;
        place += 1;
        dif += 1;
        while(fscanf(f, "%f", &num) == 1)
    
        {   
            
            dif += 1;
            place += 1;
            res += num;
            if(*max < num)
        
            {
            
                *sec_max = * max; 
                *max = num;
                place = 0;
            
            }
        
        }
    
    }

    *pos = dif - place;

    return res;    
}


void summa(FILE *f, float *max, float *sec_max)
{
    float num;
    printf("ok -- %f", *max);
    if(fscanf(f, "%f", &num) == 1)

    {
        while((num != *max) && (num != *sec_max))
    
        {   
 
            fscanf(f, "%f", &num);
            printf("%f\n", num);

        }
    
    }
    // rewind()
    // if(fscanf(f, "%f", &num) == 1)
    
    // {
    
    //     while(num != *sec_max)
        
    //     {

    //         fscanf(f, "%f", &num);
    //         printf("123\n");

    //     }
    
    // }
    
}