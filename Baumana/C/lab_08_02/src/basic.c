#include "libmy.h"
/// Блок уменьшения размера матрицы 
/// -------------------------------
void row_change(int **ptr, size_t *row, size_t pos_row)
{
    if (pos_row != *row - 1)
    {
        while (pos_row != ((*row) - 1))
        {
            int *tmp = ptr[pos_row];
            ptr[pos_row] = ptr[pos_row + 1];
            ptr[pos_row + 1] = tmp;
            pos_row++;
        }
    }
    (*row)--;
}

void col_change(int **ptr, size_t *col, size_t row, size_t pos_col)
{   
    if (pos_col != *col - 1)
    {
        for (size_t i = pos_col; i < *col - 1; ++i)
        {
            for (size_t k = 0; k < row; ++k)
            {
                swap(&ptr[k][i], &ptr[k][i + 1], sizeof(int));
            }
        }
    }
    (*col)--;
}


void swap(void *ptrl, void *ptrr, size_t elem_size)
{
    char tmp;
    char *left = ptrl;
    char *right = ptrr;
    for (size_t i = 0 ; i < elem_size; ++i, ++right, ++left)
    {
        tmp = *right;
        *right = *left;
        *left = tmp;
    }
}

/// Функция изменяет размер матрицы в меньшую сторону 
/// (меняет строки и колонки до переданного размера)
int **matrix_resize(int **ptr, size_t *row, size_t *col, size_t expected_size)
{
    size_t row_b = *row, max_row, max_col;
    max_find(ptr, *row, *col, &max_row, &max_col);    
    while (*row > expected_size)
    {
        row_change(ptr, row, max_row);
        max_find(ptr, *row, *col, &max_row, &max_col);    
    }
    while (*col > expected_size)
    {
        col_change(ptr, col, *row, max_col);
        max_find(ptr, *row, *col, &max_row, &max_col);    
    }
    int **tmp = matrix_input(*row, *col);
    if (!tmp)
        return NULL;
    for (size_t i = 0; i < *row; ++i)
    {
        for (size_t k = 0; k < *col; ++k)
        {
            tmp[i][k] = ptr[i][k];
        }
    }
    matrix_free(ptr, row_b);
    return tmp;
} 


void max_find(int **ptr, size_t row, size_t col, size_t *max_row, size_t *max_col)
{
    int max = ptr[0][0];
    for (size_t i = 0; i < row; ++i)
    {
        for (size_t k = 0; k < col; ++k)
        {
            if (ptr[i][k] >= max)
            {
                max = ptr[i][k];
                *max_row = i;
                *max_col = k;
            }
        }
    }
}

/// Блок увеличения матрицы
/// -----------------------
int row_add(int **ptr, size_t *row, size_t col)
{
    int *sum_arr = malloc(sizeof(int) * col);
    if (!sum_arr)
        return 1;
    for (size_t i = 0 ; i < col; ++i)
    {
        int sum = 0;
        for (size_t k = 0; k < *row; ++k)
        {
            sum += ptr[k][i];
        }
        sum = (int) sum / (int)(*row); // type of sum (int or double)
        sum_arr[i] = sum;
    }
    (*row)++;
    for (size_t i = 0; i < col; ++i)
    {
        ptr[*row - 1][i] = sum_arr[i];
    }

    free(sum_arr);
    return 0;
}

int col_add(int **ptr, size_t row, size_t *col, size_t expected_size)
{
    int *min_arr = malloc(sizeof(int) * row);
    if (!min_arr)
        return 1;
    for (size_t i = 0 ; i < row; ++i)
    {
        int min = ptr[i][0];
        for (size_t k = 0; k < *col; ++k)
        {
            if (ptr[i][k] < min)
            {
                min = ptr[i][k];
            }
        }
        min_arr[i] = min;
    }
    while ((*col) < expected_size)
    {
        (*col)++;
        for (size_t i = 0; i < row; ++i)
            ptr[i][*col - 1] = min_arr[i];
    }
    free(min_arr);
    return 0;
}


/// Функция изменяет размер матрицы в большую сторону
///
int **matrix_add(int **ptr, size_t *row, size_t *col, size_t expected_size)
{
    int **tmp = matrix_input(expected_size, expected_size);
    if (!tmp)
        return NULL;
    for (size_t i = 0; i < *row; ++i)
    {
        for (size_t k = 0; k < *col; ++k)
        {
            tmp[i][k] = ptr[i][k];
        }
    }
    matrix_free(ptr, *row);
    while ((*row) < expected_size)
    {
        row_add(tmp, row, *col);
    }
    col_add(tmp, *row, col, expected_size);
    
    return tmp;
}

int **matrix_multi(int **ptra, int **ptrb, size_t row)
{
    int **tmp = matrix_input(row, row);
    if (!tmp)
        return NULL;
    for (size_t i = 0; i < row; ++i)
    {
        for (size_t k = 0; k < row; ++k)
        {
            tmp[i][k] = 0;
            for (size_t l = 0; l < row; ++l)
            {
                tmp[i][k] += ptra[i][l] * ptrb[l][k];
            }   
        }
    }
    matrix_free(ptra, row);
    return tmp;
}

int **matrix_sum_line(int **ptra, int **ptrb, size_t row)
{
    int **tmp = matrix_input(row, row);
    if (!tmp)
        return NULL;
    for (size_t i = 0; i < row; ++i)
    {
        for (size_t k = 0; k < row; ++k)
        {
            tmp[i][k] = 0;
            for (size_t l = 0; l < row; ++l)
            {
                tmp[i][k] += ptra[i][l] * ptrb[l][k];
            }   
        }
    }
    matrix_free(ptra, row);
    return tmp;
}

int **multiply(int **ptra, int **ptrb, size_t row, size_t expected)
{
    int **index = NULL;
    if (expected == 0)
    {
        matrix_free(ptra, row);
        if ((index = matrix_one(row)) == NULL)
            return NULL;
    }
    else if (expected == 1)
    {
        return ptra;
    }
    else 
    {
        if ((index = matrix_multi(ptra, ptrb, row)) == NULL)
            return NULL;
        size_t i = 2;
        while (i < expected)
        {
            index = matrix_sum_line(index, ptrb, row);
            ++i;
        }
    }
    return index;
}

int **matrix_one(size_t row)
{
    int **tmp = matrix_input(row, row);
    if (!tmp)
        return NULL;
    for (size_t i = 0; i < row; ++i)
    {
        for (size_t k = 0; k < row; ++k)
        {
            if (i == k)
            {
                tmp[i][k] = 1;
            }
            else 
            {
                tmp[i][k] = 0;
            }
        }
    }
    return tmp;
}
