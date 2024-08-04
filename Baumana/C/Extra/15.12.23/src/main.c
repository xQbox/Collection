#include <stdio.h>
#include "error.h"
#include "book.h"
#include "book_array.h"


int main(int argc, char **argv)
{
    FILE *f;
    struct book_t *pbooks = NULL;
    int n_books = 0;
    int rc;
    
    if (argc != 2)
    {
        printf("app.exe file_name");
        
        return ERR_ARGS;
    }
    
    f = fopen(argv[1], "r");
    if (f)
    {
        rc = ba_create(f, &pbooks, &n_books);
        if (rc == ERR_OK)
        {
            ba_print(stdout, pbooks, n_books);
            
            ba_sort(pbooks, n_books, book_cmp_by_title);

            ba_print(stdout, pbooks, n_books);

            ba_free(pbooks, n_books);
        }
            
        fclose(f);
    }
    else
        rc = ERR_IO;
    
    return rc;
}
