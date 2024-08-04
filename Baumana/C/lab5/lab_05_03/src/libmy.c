/*  
    Целочисленный тип: int
    Метод сортировки: Пузырек
    Порядок сортировки: От меньшего к большему
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libmy.h"
#define ERROR_Wrong_Input 1
#define true 1
#define false 0
#define ERROR_Bad_Input 2
#define ERROR_Arg 3
#define ERROR_Outside 4

int write_random_int(char *filename, int range)

{
    
    if (range > 0)

    {
    
        FILE *f;

        if ((f = fopen(filename, "w+")) == NULL )

        {
            
            printf("Invalid filename\n");
            return 1;

        }

        else 

        {
            
            srand(time(NULL));
            for(int i = 0 ; i < range; i++)

            {

                int res = rand() % 1000 - 500;

                res *= res;
                fwrite(&res, sizeof(int), 1, f);
            
            }

            fclose(f);

        }

        return ERROR_Wrong_Input;

    }
    
    return 0;

}


int printFile(char *filename)

{

    FILE *f;

    if ((f = fopen(filename, "r")) == NULL)
    
    {
    
        printf("Invalid filename\\n");

        return 1;
    
    }
    
    else
    
    {

        int value;
        
        printf("\nIn file --> ");
        
        while(fread(&value, sizeof(int), 1, f) != 0)
        
        {

            printf("  %d  ", value);
        
        }

        fclose(f);
    
    }

    return 0;
}

int put_number_by_pos(FILE *f, int *value, int shift)

{
    
    if ((fseek(f, (shift * sizeof(int)), SEEK_SET)) == 0)
    
    {

        fwrite(value, sizeof(int), 1, f);
        fseek(f, (shift * sizeof(int)), SEEK_SET);   

    }

    else 

    {

        printf("Error: outside of file\n");
        
        return ERROR_Outside;

    }

    return 0;

}


int get_number_by_pos(FILE *f, int *value, int shift)

{
   
    if ((fseek(f, (shift * sizeof(int)) , SEEK_SET) == 0))
    
    {
        
        if ((fread(value, sizeof(int), 1, f)) == 1)
        
        {
            
            return 0;

        }
        
        else 

        {

            printf("Error: bad input data2 \n");
            
            return ERROR_Bad_Input;

        }
    
    }

    else 

    {

        printf("Error: outside of file");

        return  ERROR_Outside;

    }

    return 0;

}


int buble_sort(char *filename)

{
    FILE *f;
    int value;
    int maxim;
    int pos = 1;
    long size_of_file;

    f = fopen(filename, "r+");

    fseek(f, 0, SEEK_END);
    size_of_file = ftell(f); 
    fseek(f, 0, SEEK_SET);

    while (pos < ((int) ((size_of_file / sizeof(int)))))
    
    {
        
        int i = 0;

        while (i < (((int) (size_of_file / sizeof(int))) - pos))
        
        {
            
            
            
            get_number_by_pos(f, &value, (i + 1));
            get_number_by_pos(f, &maxim, i);

            if (maxim >= value)
            
            {

                put_number_by_pos(f, &value, i);
                put_number_by_pos(f, &maxim, (i + 1));

            }

            i += 1;

        }
            
        pos += 1;

    }

    printFile("new.bin");
    return 0;
}
