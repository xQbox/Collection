#include "libmy.h"


int add_a(int *array, size_t *k)
{
    int tmp;
    if ((scanf("%d", &tmp)) != 1)
        return ERR_NUM_INPUT;
    array[*k] = tmp;
    (*k)++;
    return ERR_OK;
}

void delete_a(int *array, size_t *k)
{
    array[*k] = 0;
    (*k)--; 
}

