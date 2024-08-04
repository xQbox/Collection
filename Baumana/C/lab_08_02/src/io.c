#include "libmy.h"

int number_check(size_t *number)
{
    int tmp; 
    // printf("Введите число: ");
    if ((fscanf(stdin, "%d", &tmp)) != 1)
        return ERR_IO;
    if (tmp < 1)
        return ERR_RANGE;
    *number = tmp;
    return ERR_OK;
}

int input(int *data)
{
    int tmp;
    if ((fscanf(stdin, "%d", &tmp)) != 1)
        return ERR_IO;
    *data = tmp;
    return ERR_OK;
}

int input_size(size_t *data)
{
    int tmp; 
    // printf("Введите число: ");
    if ((fscanf(stdin, "%d", &tmp)) != 1)
        return ERR_IO;
    if (tmp < 0)
        return ERR_RANGE;
    *data = tmp;
    return ERR_OK;
}

int matrix_data(int **ptr, size_t row, size_t col)
{
    for (size_t i = 0; i < row; ++i)
    {
        for (size_t k = 0; k < col; ++k)
        {
            // printf("Введите данные [%d][%d]: ", i + 1, k + 1);
            if ((input(&ptr[i][k])) != ERR_OK) 
                return ERR_IO;
        }
    }
    return ERR_OK;
}


void matrix_print(int **ptr, size_t row, size_t col)
{
    for (size_t i = 0; i < row; ++i)
    {
        for (size_t k = 0; k < col; ++k)
            printf("%d\n", ptr[i][k]);
        printf("\n");
    }
}

int **create_matrix(int **ptr, size_t row)
{
    int **tmp = calloc(row, sizeof(int *));
    if (!tmp)
        return NULL;
    for (size_t i = 0 ; i < row; ++i)
    {
        tmp[i] = malloc(row * sizeof(int));
    }
    for (size_t i = 0; i < row; ++i)
    {
        for (size_t k = 0 ; k < row; ++k)
        {
            tmp[i][k] = ptr[i][k];
        }
    }
    return tmp;
}
