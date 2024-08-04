#include "libmy.h"



int base(struct long_number_t *number)
{
    // Ввод мантиссы
    int rc, order_n = 0; 
    char tmp;
    char Whole_number[ARR_LEN - 8];

    if ((rc = struct_input(number)) != ERR_OK)
        return rc;
    scanf("%c", &tmp);
    // ввод целого числа для умножения
    if ((rc = number_input(Whole_number)) != ERR_OK)
        return rc;
    size_t tmp1  = strlen(Whole_number); 
    Whole_number[strlen(Whole_number)] = '.';
    Whole_number[tmp1 + 1] = 0; 

    size_t point_position = tmp1; 
    if (((rc = normalized_number(Whole_number, &order_n, &point_position))) != ERR_OK)
        return rc;
    printf("\nИтоговое число:\n>+---------1---------2---------3---------4---------5\n  %s E %d\n", Whole_number, order_n);
    
    // Обработать варианты знака результата
    int New_number[ARR_LEN - 8];
    int New_mantissa[ARR_LEN + 3];
    int order_general = order_n + number->order;
    char flag = ' ';
    size_t number_size = 0, mantissa_size = 0;

    if (((Whole_number[0] == '-') && (number->mantissa[0] != '-')) || ((number->mantissa[0] == '-') && (Whole_number[0] != '-')))
        flag = '-';
    // создание массива интов
    from_char_to_int(number->mantissa, strlen(number->mantissa), New_mantissa, &mantissa_size);
    from_char_to_int(Whole_number, strlen(Whole_number), New_number, &number_size);
    
    if ((rc = multiply(New_mantissa, mantissa_size, New_number, number_size, &order_general, flag)) != ERR_OK)
        return rc;

    return ERR_OK;
}


int multiply(int *arr_m, size_t size_m, int *arr_n, size_t size_n, int *order, char flag)
{
    int R[ARR][ARR];
    /// Изменен диапазон с size_n до size_n - 1 (аналогично  с size_m)
    for (int i = (int) size_n - 1; i > -1; i--)
    {
        for (int k = (int) size_m - 1; k > -1; k--)
        {
            R[i][k] = arr_m[k] * arr_n[i];  
        }
    }

    mass_summa(R, &size_n, &size_m);
    if (size_m > (ARR_LEN - 11))
        left_shift(R[0], size_m, order);


    if ((*order < -99999) || (*order > 99999))
        return ERR_RANGE;
    size_t index = 0;
    // добавлен блок кода между комментариями
    while (R[0][index] == 0)
        index ++;
    if (index > 0)
        *order -= index;
    if ((*order < -99999) || (*order > 99999))
        return ERR_RANGE;
    if (index > 0)
    {

        if ((size_m - index) > (ARR_LEN - 10))
        {
            printf("\nИтоговое число:\n>+---------1---------2---------3---------4---------5\n%c.", flag);
            
            for (int i =  index ; i < ARR_LEN - 10; i++)
            {
                printf("%d", R[0][i]);
            }
            printf(" E %d", *order);
        }
        else
        {
            printf("\nИтоговое число:\n>+---------1---------2---------3---------4---------5\n%c.", flag);
            
            for (size_t i =  index ; i < size_m; i++)
            {
                printf("%d", R[0][i]);
            
            }
            printf(" E %d", *order);
        }
            
        return ERR_OK;
    }
    // добавлен блок кода
    if (size_m >= (ARR_LEN - 10))
    {
        printf("\nИтоговое число:\n>+---------1---------2---------3---------4---------5\n%c.", flag);
        
        for (int i =  0 ; i < ARR_LEN - 10; i++)
        {
            printf("%d", R[0][i]);
        }
        printf(" E %d", *order);
    }
    else
    {
        printf("\nИтоговое число:\n>+---------1---------2---------3---------4---------5\n%c.", flag);
        
        for (size_t i =  0 ; i < size_m; i++)
        {
            printf("%d", R[0][i]);
        }
        printf(" E %d", *order);
    }
    return ERR_OK;
}


int cycle_shift(int *arr, size_t size_arr)
{ 
    int std_temp = arr[size_arr];
    for (int i = (int) size_arr; i > -1; i--)
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
    return ERR_OK;
}

int mass_summa(int arr[ARR][ARR], size_t *row, size_t *column)
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
        size_t temp = i;
        while (temp > 0) 
        {
            cycle_shift(arr[i], *column);
            temp --;
        }
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

    change_order(arr[0], *column);

    return ERR_OK;
}


int change_order(int *arr, size_t arr_size)
{
    for (size_t i = arr_size - 1; i > 0; i--)
    {
        arr[i - 1] = arr[i - 1] + arr[i] / 10;
        arr[i]  %= 10;
    }
 
    return ERR_OK;
}


int from_char_to_int(char *arr, size_t arr_len, int *number, size_t *size)
{
    size_t i = 1;
    if (arr[0] == '-')
        i += 1;
    for (; i < arr_len; i++)
    {
        number[*size] = arr[i] - '0';
        *size += 1;
    }
    return ERR_OK;
}

int normalized_number(char *mantissa, int *order, size_t *point_position)
{
    size_t i = 0;
    int count = 0;
    if (mantissa[0] == '-')
        i += 1;
    while (mantissa[i] != '.')
    {
        char temp = mantissa[*point_position - 1];
        mantissa[*point_position - 1] = mantissa[*point_position];
        mantissa[*point_position] = temp;
        *point_position -= 1;
        count += 1; 
    }
    *order += count;
    
    return ERR_OK;
} 

void print_arr(int *arr, int size)
{
    printf("\n");
    for(int i = 0; i < size; i++)
        printf("%3d", arr[i]);
    printf("\n");
}

int left_shift(int *arr, size_t size, int *order)
{
    if (size > ARR_LEN - 11)
    {
        int tmp = arr[0];
        if (arr[ARR_LEN - 10] >= 5)
            arr[ARR_LEN - 11] += 1;
        for(int i =  ARR_LEN - 11; i > -1; i--)
        {
            if(arr[i] == 10)
                arr[i - 1] += 1;
            else
                break;
        }
        if (tmp != arr[0])
        {
            *order += 1;
            for(size_t i = 1; i < size + 1; i++)
                if (arr[i] > 9)
                    arr[i] %= 10; 
        }
    }
    // if (size > ARR_LEN - 11)
    // {
    //     int tmp = arr[0];
    //     for(int i = (int) size; i > -1; i--)
    //     {
    //         if (arr[i] >= 5)
    //             arr[i - 1] += 1;

    //     }
    // // добавлен блок кода до конца
    //     if (tmp != arr[0])
    //     {
    //         *order += 1;
    //         for(size_t i = 1; i < size + 1; i++)
    //             if (arr[i] > 9)
    //                 arr[i] %= 10; 
    //     }
    // }
    return ERR_OK;
}
