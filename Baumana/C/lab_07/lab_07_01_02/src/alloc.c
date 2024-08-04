#include "libmy.h"

int *create_array(size_t a_n)
{
    int *ptr;
    ptr = malloc(a_n * sizeof(int));
    if (!ptr)
        return NULL;
    return ptr;
}

void clear_array(int *a)
{
    free(a);
}
