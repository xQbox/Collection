#include "libmy.h"

void buble_sort(int *arr, int n)
{
    for(int k = 0; k < n; k++)
    {
        for(int i = 0; i < n - k - 1; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                int temp = arr[i + 1];
                arr[i + 1] = arr[i];
                arr[i] = temp;
            }
        }
    }
}


// block of new array
int funcion(const int *ptrs, const int *ptrend, size_t *size)
{
    int index = 0;
    int i = ptrend - ptrs; 
    while ((index < i) &&  (*(ptrs + index) > -1))
    {
        *size += 1;
        index += 1;
    }
    if (*size == 0)
        return ERR_ARR_SIZE;
    
    return ERR_OK;
}

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    if (((pb_src == pe_src) || (pb_src > pe_src)) || ((pb_src == NULL) || (pe_src == NULL)))
        return ERR_SIZE;
    int rc = ERR_OK;
    size_t size = 0;

    if ((rc = funcion(pb_src, pe_src, &size)) != ERR_OK)
        return rc;
    *pb_dst = create_array(size);
    if (!(*pb_dst))
        return ERR_MEM;
    int *ptrtemp = *pb_dst;
    for (*pe_dst = ptrtemp + size; ptrtemp < *pe_dst; pb_src++, ptrtemp++)
        *ptrtemp = *pb_src;

    return rc;
}


// block of sorting funcion

void mysort(void *data, size_t num, size_t elem_size, int(*comp) (const void *, const void *))
{
    char *ptrs = data;
    char *ptrend = ptrs + (num * elem_size);
    size_t k = 0;
    for(char *ps = ptrs; ps < ptrend; ps+=elem_size)
    {
        for(char *ps_n = ptrs; ps_n < ptrend - elem_size - (elem_size * k); ps_n+=elem_size)
        {
            if(comp(ps_n, ps_n + elem_size) > 0)
            {
                swap(ps_n, ps_n + elem_size, elem_size);
            }
        }
        k += 1; 
    }
}

int comp(const void *left, const void *right)
{
    const int *pl = left;
    const int *pr = right;
    return *pl - *pr;
}

void swap(void *left, void *right, size_t elem_size)
{
    char tmp;
    char *pl = left;
    char *pr = right;
    for (size_t i = 0; i < elem_size; i++, pl++, pr++)
    {
        tmp = *pl;
        *pl = *pr;
        *pr = tmp;
    }
}


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
        case ERR_SIZE:
            fprintf(stdout, "Ошибка некорректного размера массива\n");
            break;
    }
}
