#include "libmy.h"

struct item_t *arr_create(size_t size, struct item_t *item)
{
    struct item_t *ptr = NULL;
    ptr = calloc(size, sizeof(struct item_t));
    if (!ptr)
        return NULL;
    return ptr;
}

void arr_free(struct item_t *ptr)
{
    free(ptr);
}

void item_free(struct item_t *ptr)
{
    free(ptr->item_name);
    ptr->item_name = NULL;
}

void ai_free(struct item_t *ptr, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        item_free(&ptr[i]);
    }
    arr_free(ptr);
}
