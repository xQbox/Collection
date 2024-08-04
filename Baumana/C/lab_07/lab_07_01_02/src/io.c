#include "libmy.h"

int file_check(char *filename, size_t *elem_count)
{
    FILE *f;
    if ((f = fopen(filename, "r+")) ==  NULL)
        return ERR_FILE_OPEN;
    int temp;

    while((fscanf(f, "%d", &temp)) == 1)
        *elem_count += 1;
    if (!(feof(f)))
        return ERR_FILE_IO;
    if (*elem_count == 0)
        return ERR_EMPTY_FILE;
    if (fclose(f) != 0)
        return ERR_FILE_CLOSE;
    
    return ERR_OK;
}

int arr_create(char *filename, int *ptrs)
{
    FILE *f;
    if ((f = fopen(filename, "r+")) ==  NULL)
        return ERR_FILE_OPEN;
    int temp;

    while((fscanf(f, "%d", &temp)) == 1)
    {
        *ptrs = temp;
        ptrs ++;
    }
    if (!(feof(f)))
        return ERR_FILE_IO;
    if (fclose(f) != 0)
        return ERR_FILE_CLOSE;

    return ERR_OK;
}

void print_arr(int *ptrs, int *ptrend)
{
    printf("ARRAY: \n\t");
    for (int *i = ptrs; i < ptrend; i += 1) // Idea to increase += sizeof(int)
        printf("%3d ", *i);
    printf("\n");
}

int file_write(char *filename, int *ptrs, int *pend)
{
    FILE *f;
    if ((f = fopen(filename, "w")) ==  NULL)
        return ERR_FILE_OPEN;
 
    for(int *i = ptrs; i < pend; i += 1)
        fprintf(f, "%3d ", *i);

    if (fclose(f) != 0)
        return ERR_FILE_CLOSE;
    return ERR_OK;
}
