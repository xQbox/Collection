#include "libmy.h"

int ai_init(char *filename, size_t *size, struct item_t **ptr)
{
    int rc = ERR_OK;
    *ptr = NULL;
    rc = ai_count(filename, size);
    if (rc == ERR_OK)
    {
        struct item_t *ptrs = calloc(1, sizeof(struct item_t));
        if (ptrs)
        {
            rc = elem_count(filename, *size, ptrs);
            if (rc == ERR_OK)
            {
                *ptr = calloc(*size, sizeof(struct item_t));
                if (!ptr)
                    rc = ERR_MEM;
            }
            free(ptrs);
        }
        else
        {
            rc = ERR_MEM;
        }
    }
    return rc;
}

void swap(struct item_t *left, struct item_t *right)
{
	struct item_t tmp = *right;
    *right = *left;
    *left = tmp;
}

int comp(double left, double right)
{
    if (left - right > 0)
        return 1;
    else 
        return -1;
}

void buble_sort(struct item_t *ptr, size_t size, int (*comp)(double left, double right))
{
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t k = 0; k < size - i - 1; ++k)
        {
            if (comp(ptr[k].mas / ptr[k].volume, ptr[k + 1].mas / ptr[k + 1].volume) > 0)
            {
                swap(&ptr[k], &ptr[k + 1]);
            }
        }
    }
    for (size_t i = 0; i < size; ++i)
    {
        item_print(&ptr[i]);
    }
}

int substring_collect(char *substring, char *item_name)
{
    size_t minim = MIN(strlen(substring), strlen(item_name));
    for (size_t i = 0; i < minim; ++i)
    {
        if (substring[i] != item_name[i])
            return 1;
    }
    return 0;
}

int substring_find(char *substring, struct item_t *ptr, size_t size)
{
    size_t flag = 0;
    for (size_t i = 0; i < size; ++i)
    {
        if (!(substring_collect(substring, ptr[i].item_name)))
        {    
            flag = 1;
            item_print(&ptr[i]);
        }
    }

    return (flag == 1) ? (ERR_OK) : (ERR_SUBSTRING); 
}

void sort(struct item_t *ptr, size_t size)
{
    buble_sort(ptr, size, &comp);
}   



int ai_create(char *filename, size_t size, struct item_t *ptr)
{
    FILE *f;
    int rc = ERR_OK;
    f = fopen(filename, "r");
    for (size_t i = 0; i < size; ++i)
    {
        rc = item_read(f, &ptr[i]);
    }
    if (feof(f))
        rc = ERR_OK;
    fclose(f);
    return rc;
}
