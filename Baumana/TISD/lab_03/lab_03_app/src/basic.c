#include "libmy.h"

void matrix_p_init(int **ptr, size_t row, size_t col, int *ptrd, size_t *index) 
{
    int sum = 0;
	for (size_t i = 0; i < row; ++i)
    {
        int value = 0;
        for (size_t k = 0; k < col; ++k)
        {
            if (ptr[i][k] > 0)
            {
                value++;
            }   
        }
        sum += value;
        ptrd[*index] = sum;
        (*index)++;
    }
}

int percent_read(size_t *percent, size_t row, size_t col)
{
    if (col == 1)
    {
        printf("Введите процент [%%] разреженности вектора:\n>>");
    }
    else
    {
        printf("Введите процент [%%] разреженности матрицы:\n>>");
    }
    int tmp;
    if ((fscanf(stdin, "%d", &tmp)) != 1)
        return ERR_NUM_INPUT;
    if ((tmp < 0) || (tmp > 100))
        return ERR_RANGE;
    *percent = percent_count(tmp, row, col);
    return ERR_OK;
}

size_t percent_count(size_t percent, size_t row, size_t col)
{
    return  (((row * col) * (percent)) / 100);  
}


int *pointer_init(int *ptr, size_t size_p, size_t all_size)
{
    int *tmp = calloc(all_size, sizeof(int));
    if (!tmp)
        return NULL;

    for (size_t i = 0; i < size_p ; ++i)
    {
        tmp[ptr[i] - 1] = i + 1;
    }
    return tmp;
}

/// Miltiply Matrix and vector (matrix consisting of three arrays and vector consisting of two arrays)
/// Return  result
int *multiply_matrix_and_column_vector(int *ptr_values, int *ptr_columns, int *ptr_row_pointers, size_t ptr_colum_size, int *vector_values, int *vector_index, int *res)
{
    int summa = 0;
    size_t index = 1;
    for (size_t i = 0; i < ptr_colum_size; ++i)
    {
        if ((int) (i+1) > ptr_row_pointers[index])
        {
            res[index - 1] = summa;
            summa = 0;
            index ++;
        }
        if ((vector_index[ptr_columns[i] - 1] != 0) && (ptr_columns[i] != 0))
        {
            summa += ptr_values[i] * vector_values[vector_index[ptr_columns[i] - 1] - 1];
        }
    }
    res[index - 1] = summa;
    return res;
}

void structur_init(int **ptr, size_t row, size_t col, int *a_values, int *a_pos_colum, int *a_pos_row)
{
    int index = 0, sum = 0;

    for (size_t i = 0; i < row; ++i)
    {
        for (size_t k = 0; k < col; ++k)
        {
            if (ptr[i][k] != 0)
            {
                a_values[index] = ptr[i][k];
                a_pos_colum[index] = k + 1;
                sum++;
                index++;
            }
        }
        a_pos_row[i + 1] = sum;
    }
}

int *multiply_matrix(int **ptr, size_t row, size_t col, int *ptr_v, int *res)
{
    size_t index = 0;
    // int *res = calloc(row, sizeof(int));
    // if (!res)
    //     return NULL;
    size_t counter = 0;
    for (size_t i = 0; i < row; ++i)
    {
        int sum = 0;
        for (size_t k = 0; k < col; ++k)
        {
            sum += ptr[i][k] * ptr_v[k];
            counter++;
        }
        res[index] = sum;
        index++;
    }
    // printf("Счетчик итерации ->%ld\n", counter);
    return res;
}

void random_input(int **ptr, size_t row, size_t col, size_t sparse_percentage, size_t *count_of_values)
{
    while (sparse_percentage  > *count_of_values)
    {
        int tmp_row = rand() % row;
        int tmp_col = rand() % col;
        if ((ptr[tmp_row][tmp_col] == 0))
        {
            long int time_s;
            time_s = time(NULL);
            srand(time_s);
            int tmp = rand() % 1000;
            // значение выше исправлено (5 ---> 1000) для замеров  
            if ((tmp != 0))
            {
                ptr[tmp_row][tmp_col] = tmp;
                (*count_of_values)++;
            }
        }
    }
}
