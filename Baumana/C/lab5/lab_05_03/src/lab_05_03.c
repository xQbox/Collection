#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libmy.h"
#define ERROR_Wrong_Input 1
#define true 1
#define false 0
#define ERROR_Bad_Input 2
#define ERROR_Arg 3



int buble_sort();
int write_random_int();
int printFile();
int get_number_by_pos();
int put_number_by_pos();


int main(int argc, char **argv)
{
    
    if (argc != 3)
    
    {
    
        return ERROR_Arg;
    
    }
    
    char *filename;

    filename = argv[2]; 
    
    if (atoi(argv[1]) > 0)
    
    {

        write_random_int(filename, atoi(argv[1]));
        printFile(filename);

    }
    
    else
    
    {

        printf("Error, bad arguments\n");
        
        return ERROR_Arg;

    }
    


    buble_sort(filename);
    printFile(filename);
    return 0;

}
// int main(int argc, char *argv[])
// {
//     if (argc != 3) 
//         return ERR_ARGS;

//     int error;
//     int count_elems = atoi(argv[1]);
//     if (count_elems > 0)
//     {
//         error = create_file(argv[2], count_elems);
//         if (error != EXIT_SUCCESS)
//             return error;
//     }
//     else if (strcmp(argv[1], "p") == 0)
//     {
//         error = print_file(argv[2]);
//         if (error != EXIT_SUCCESS)
//             return error;
//     }
//     else if (strcmp(argv[1], "s") == 0)
//     {
//         error = sort_file(argv[2]);
//         if (error != EXIT_SUCCESS)
//             return error;
//     }
//     else 
//     {
//         return ERR_ARGS;
//     }

//     return EXIT_SUCCESS;
// }
