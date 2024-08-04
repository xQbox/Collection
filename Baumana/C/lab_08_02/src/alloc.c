#include "libmy.h"

void matrix_free(int **ptr, size_t row)
{
    for (size_t i = 0; i < row; ++i)
    {
        free(ptr[i]);
    }
    free(ptr);
}


int **matrix_input(size_t row, size_t col)
{
    int **tmp_ptr = NULL;
    tmp_ptr = calloc(row, sizeof(int *));
    if (!tmp_ptr)
        return NULL;
    
    for (size_t i = 0; i < row; ++i)
    {
        tmp_ptr[i] = malloc(col * sizeof(int));
        if (!tmp_ptr[i])
        {
            matrix_free(tmp_ptr, row);
            return NULL;
        }
    }

    return tmp_ptr;
}
