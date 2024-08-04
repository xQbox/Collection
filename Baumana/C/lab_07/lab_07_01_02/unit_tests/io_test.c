#include "libmy.h"
#define ARR_SIZE 10

void show_err_message(int rc)
{
    fprintf(stdout, "Error:\n\t");
    printf("rc = %d\n\t", rc);
    switch (rc)
    {
        case ERR_DATA_FILE:
            fprintf(stdout, "Ошибка некорректного файла\n");
            break;   
        case ERR_FILE_OPEN:
            fprintf(stdout, "Невозможно открыть файл\n");
            break;
        case ERR_FILE_CLOSE:
            fprintf(stdout, "Невозможно закрыть файл\n");
            break;
        case ERR_FILE_IO:
            fprintf(stdout, "Ошибка считывания данныx из файла\n");
            break;
        case ERR_EMPTY_FILE:
            fprintf(stdout, "Ошибка пустой файл\n");
            break;
        case ERR_OK:
            fprintf(stdout, "Программа отработала корректно\n");
            break;
        case ERR_ARR_SIZE:
            fprintf(stdout, "Ошибка неправильного размера функции-фильтра\n");
            break;
        case ERR_MEM:
            fprintf(stdout, "Ошибка выделения памяти\n");
            break;
        case ERR_ARG_BAD :
            fprintf(stdout, "Ошибка невалидных входных данных командной строки\n");
            break;
    }
}


int main()
{
    int count = 0;
    {
        printf("\nТест %d для функции check_file:\n\t", count);
        count += 1;
        char *filename = "INFILE0.txt";
        size_t elem = 0;
        int rc;
        if ((rc = file_check(filename, &elem)) != ERR_OK)
        {
            printf("rc = %d\n\t", rc);
            show_err_message(rc);
        }
        if (elem != 10)
            printf("\nERROR count elements of array\n");    
        if (rc == ERR_OK)
            printf("----------------------------------------------\nTEST PASSED\n----------------------------------------------\n");
        else 
            printf("----------------------------------------------\nTEST FAILED\n----------------------------------------------\n");
    
    }
    {
        printf("\nТест %d для функции check_file:\n\t", count);
        count += 1;
        char *filename = "INFILE1_NEG.txt";
        size_t elem = 0;
        int rc;
        if ((rc = file_check(filename, &elem)) != ERR_OK)
        {   
            printf("rc = %d\n\t", rc);
            show_err_message(rc);
        }
        if (elem != 10)
            printf("\nERROR count elements of array\n");
        if (rc == ERR_OK)
            printf("----------------------------------------------\nTEST PASSED\n----------------------------------------------\n");
        else 
            printf("----------------------------------------------\nTEST FAILED\n----------------------------------------------\n");
    
    }
    {
        printf("\nТест %d для функции arr_create:\n\t", count);
        count += 1;
        char *filename = "ARR_CREATE_NEG.txt";
        int A[ARR_SIZE];
        int B[ARR_SIZE] = {1, 2, 3 , 4, 5, 6, 7, 8, 9, 10};
        int rc;
        if ((rc = arr_create(filename, A)) != ERR_OK)
        {   
            printf("rc = %d\n\t", rc);
            show_err_message(rc);
        }
        for(size_t i = 0 ; i < ARR_SIZE; i++)
        {
            if (A[i] != B[i])
                rc = ERR_FILE_IO;
        }
        show_err_message(rc);
        if (rc == ERR_OK)
            printf("----------------------------------------------\nTEST PASSED\n----------------------------------------------\n");
        else 
            printf("----------------------------------------------\nTEST FAILED\n----------------------------------------------\n");
    
    }
    {
        printf("\nТест %d для функции arr_create:\n\t", count);
        count += 1;
        char *filename = "INFILE3_NEG.txt";
        int A[ARR_SIZE];
        int B[ARR_SIZE] = {0, 9 , 0 , 9, 0 , 0 , 0, 9 ,9 , 10};
        int rc;
        if ((rc = arr_create(filename, A)) != ERR_OK)
        {   
            printf("rc = %d\n\t", rc);
            show_err_message(rc);
        }
        for(size_t i = 0 ; i < ARR_SIZE; i++)
        {
            if (A[i] != B[i])
                rc = ERR_FILE_IO;
        }
        show_err_message(rc);
        if (rc == ERR_OK)
            printf("----------------------------------------------\nTEST PASSED\n----------------------------------------------\n");
        else 
            printf("----------------------------------------------\nTEST FAILED\n----------------------------------------------\n");
    
    }
    printf("\nTESTS FINISHED\n");
    return ERR_OK;
}