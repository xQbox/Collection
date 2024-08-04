#include <stdlib.h>
#include "book_array.h"


int ba_count(FILE *f, int *n)
{
    struct book_t item = { NULL, 0 };
    int           i = 0;
    int           rc = ERR_OK;
    
    while (rc == ERR_OK)
    {
        rc = book_read(f, &item);
        /*
        rc = book_read_ex(f, &item);
        */
        if (rc == ERR_OK)
        {
            i++;

            book_free_content(&item);
        }
    }

    *n = i;

    if (rc != ERR_OK && feof(f))
        rc = ERR_OK;

    return rc;
}


int ba_read(FILE *f, struct book_t *pbooks, int n)
{
    int rc = ERR_OK;
    
    for (int i = 0; rc == ERR_OK && i < n; i++)
        rc = book_read(f, pbooks + i);
        /*
        rc = book_read_ex(f, pbooks + i);
        */

    return rc;
}


int ba_create(FILE *f, struct book_t **pbooks, int *n_books)
{
    struct book_t *ptmp;
    int n;
    int rc;

    *pbooks = NULL;
    *n_books = 0;

    rc = ba_count(f, &n);
    if (rc == ERR_OK)
    {
        ptmp = calloc(n, sizeof(struct book_t));
        if (ptmp)
        {
            rewind(f);
            
            rc = ba_read(f, ptmp, n);

            if (rc == ERR_OK)
            {
               *pbooks = ptmp;
               *n_books = n;
            }
            else
            {
               ba_free(ptmp, n);
            }
        }
        else
            rc = ERR_MEM;
    }

    return rc;
}


void ba_print(FILE *f, const struct book_t *pbooks, int n)
{
    for (int i = 0; i < n; i++)
        book_print(f, pbooks + i);
}


void ba_sort(struct book_t *pbooks, int n, int (*cmp)(const void*, const void*))
{
    qsort(pbooks, n, sizeof(*pbooks), cmp);
}


void ba_free(struct book_t *pbooks, int n)
{
    for (int i = 0; i < n; i++)
        book_free_content(pbooks + i);

    free(pbooks);
}
