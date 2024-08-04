#include "libmy.h"

int cycle_shift(int *arr, size_t size_arr)
{
    int std_temp = arr[size_arr];
    for (int i = (int) size_arr - 1; i > -1; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[0] = std_temp;
    return ERR_OK;
}

int multiply_by_digit(int *arr, int a, size_t arr_size)
{
    for (size_t i = 0; i < arr_size; i++)
    {
        arr[i] = arr[i] * a; 
    }
    for (size_t i = 0; i < arr_size; i++)
    {
        printf("%d\n", arr[i]); 
    }
    return ERR_OK;
}

int mass_summ(int arr[ARR][ARR], size_t *row, size_t *column)
{
    size_t std_size = *column;
    *column = *column + *row - 1;
    for (size_t i = 0; i < *row; i++)
    {   
        for (size_t k = 0; k < *column; k++)
        {
            if (k > std_size - 1)
            {
                arr[i][k] = 0;
            }
        }
    }
    for (size_t i = 0; i < *row; i++)
    {
        for (size_t k = 0; k < *column; k++)
        {
            printf("%4d", arr[i][k]);
        }
        printf("\n");
    }
    for (size_t i = 0; i < *row; i++)
    {
        size_t temp = i;
        while (temp > 0)
        {
            cycle_shift(arr[i], *column);
            temp --;
        }
    }
    printf("\n");
    printf("\n");

    for (size_t i = 0; i < *row; i++)
    {
        for (size_t k = 0; k < *column; k++)
        {
            printf("%4d", arr[i][k]);
        }
        printf("\n");
    }

    for (size_t i = 0; i < *column; i++)
    {   
        int sum = 0;
        for (size_t k = 0; k < *row; k++)
        {
            sum += arr[k][i]; 
        }
        arr[0][i] = sum;
    }

    printf("\n");
    for (size_t k = 0; k < *column; k++)
    {
        printf("%4d", arr[0][k]);
    }
    printf("\n");
    
    change_order(arr[0], *column);
    printf("\n");

    return ERR_OK;
}

int multiply(int *arr, size_t size_arr, int *arr1, size_t size_arr1)
{
    int R[ARR][ARR];
    
    for (int i = (int) size_arr - 1; i > -1; i--)
    {
        printf("%3d", arr[i]);
    }
    printf("\n");
    for (int i = (int) size_arr1 - 1; i > -1; i--)
    {
        printf("%3d", arr1[i]);
    }
    printf("\n");
    for (int i = (int) size_arr1; i > -1; i--)
    {
        for (int k = (int) size_arr; k > -1; k--)
        {
            R[i][k] = arr[k] * arr1[i]; 
        }
    }

    for (int i = (int) size_arr1 - 1; i > -1; i--)
    {
        for (int k = (int) size_arr - 1; k > -1; k--)
        {
            printf("%3d", R[i][k]);
        }
        printf("\n");
    }
    mass_summ(R, &size_arr1, &size_arr);
    
    return ERR_OK;
}


int change_order(int *arr, size_t arr_size)
{

    for (size_t i = arr_size; i > 0; i--)
    {
        arr[i - 1] = arr[i - 1] + arr[i] / 10;
        arr[i]  %= 10;
    }
    for (size_t i = 0; i < arr_size; i++)
    {
        printf("%3d", arr[i]);
    }
    return ERR_OK;
}
// not working with point
int from_char_to_int(char *arr, size_t arr_len, int *arr_int, size_t *arr_int_len)
{
    for (size_t i = 0; i < arr_len - 1; i++)
    {
        arr_int[i] = arr[i] - '0';
    }
    *arr_int_len = arr_len - 1; 
    return ERR_OK;
}
