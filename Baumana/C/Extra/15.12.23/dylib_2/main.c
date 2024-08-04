#include <stdio.h>
#include <dlfcn.h>
#include "error.h"
#include "book.h"
#include "book_array.h"
#include <string.h>
// указатели на функции библиотеки book.h
// последняя функция не нужна
struct lib_funcs_t
{
    int (*ba_create)(FILE *f, struct book_t **pbooks, int *n_books);
    void (*ba_print)(FILE *f, const struct book_t *pbooks, int n);
    void (*ba_sort)(struct book_t *pbooks, int n, int (*cmp)(const void*, const void*));
    void (*ba_free)(struct book_t *pbooks, int n);
    // int (*book_cmp_by_title)(const void *l, const void *r);
};
int book_cmp_by_title(const void *l, const void *r)
{
    const struct book_t *pl = l;
    const struct book_t *pr = r;
    
    return strcmp(pl->title, pr->title);
}

int lib_load_funcs(void *hlib, struct lib_funcs_t *func)
{
    func->ba_create = dlsym(hlib, "ba_create");
    if (!func->ba_create)
    {
        fprintf(stderr, "cannot load ba_create:%s\n", dlerror());
        return ERR_IMPORT_FUNC;
    }
    func->ba_free = dlsym(hlib, "ba_free");
    if (!func->ba_free)
    {
        fprintf(stderr, "Can not load lib: %s\n", dlerror());
        return ERR_IMPORT_FUNC;
    }
    func->ba_print = dlsym(hlib, "ba_print");
    if (!func->ba_print)
    {
        fprintf(stderr, "cannot load ba_create:%s\n", dlerror());
        return ERR_IMPORT_FUNC;
    }
    func->ba_sort = dlsym(hlib, "ba_sort");
    if (!func->ba_sort)
    {
        fprintf(stderr, "cannot load ba_create:%s\n", dlerror());
        return ERR_IMPORT_FUNC;
    }
    return ERR_OK;
}

int process_file(const char *fname , struct lib_funcs_t *func)
{
    FILE *f;
    struct book_t *pbooks = NULL;
    int n_books = 0;
    int rc = 0;
    
    f = fopen(fname, "r+");
    if (f)
    {
        rc = func->ba_create(f, &pbooks, &n_books);
        if (rc == ERR_OK)
        {
            func->ba_print(stdout, pbooks, n_books);
            
            func->ba_sort(pbooks, n_books, book_cmp_by_title);

            func->ba_print(stdout, pbooks, n_books);

            func->ba_free(pbooks, n_books);
        }
            
        fclose(f);
    }
    else
        rc = ERR_IO;
    
    return rc;
}



int main (int argc, char **argv)
{
    void *hlib = NULL;
    int rc = ERR_OK;
    
    struct lib_funcs_t funcs = {NULL};
    if (argc != 3)
    {
        fprintf(stderr, "app.exe lib_name file_name\n");
        return ERR_ARGS;
    }
    hlib = dlopen(argv[1], RTLD_NOW);
    if (!hlib)
    {
        fprintf(stderr,"Error, cant open lib %s", dlerror());
        return ERR_LOAD_LTB;
    }
    rc = lib_load_funcs(hlib, &funcs);
    if (!rc)
        process_file(argv[2], &funcs);
    dlclose(hlib);
    return rc;
}


// #include <stdio.h>
// #include <stdlib.h>
// #include <dlfcn.h>
// #include <string.h>
// #include "error.h"
// #include "book.h"
// #include "book_array.h"

// #define ERROR_LIBRARY_OPEN 10
// #define ERROR_IMPORT_FUNC 11

// struct lib_funcs_t
// {
//     int (*ba_create)(FILE *f, struct book_t **pbooks, int *n_books);
//     void (*ba_print)(FILE *f, const struct book_t *pbooks, int n);
//     void (*ba_sort)(struct book_t *pbooks, int n, int (*cmp)(const void*, const void*));
//     void (*ba_free)(struct book_t *pbooks, int n);
// };

// int process_file(const char *fname, struct lib_funcs_t *funcs);

// int book_cmp_by_title(const void *l, const void *r)
// {
//     const struct book_t *pl = l;
//     const struct book_t *pr = r;
    
//     return strcmp(pl->title, pr->title);
// }

// int book_cmp_by_year(const void *l, const void *r)
// {
//     const struct book_t *pl = l;
//     const struct book_t *pr = r;
    
//     return pl->year - pr->year;
// }

// int lib_load_funcs(void *hlib, struct lib_funcs_t *funcs);

// int main(int argc, char **argv)
// {
//     void *hlib = NULL;
//     struct lib_funcs_t funcs = {NULL};
//     int rc;

//     if (argc != 3)
//     {
//         printf("app.exe libname file_name");
//         return ERR_ARGS;
//     }

//     hlib = dlopen(argv[1], RTLD_NOW);
//     if (!hlib)
//         return ERROR_LIBRARY_OPEN;
    
//     rc = lib_load_funcs(hlib, &funcs);
//     if (rc)
//     {
//         dlclose(hlib);
//     }

//     if (!rc)
//     {
//         rc = process_file(argv[2], &funcs);
//     }
//     dlclose(hlib);
//     return 0;
// }

// int process_file(const char *fname, struct lib_funcs_t *funcs)
// {
//     FILE *f;
//     struct book_t *pbooks = NULL;
//     int n_books = 0;
//     int rc;

//     f = fopen(fname, "r");
//     if (f)
//     {
//         rc = funcs->ba_create(f, &pbooks, &n_books);
//         if (rc == ERR_OK)
//         {
//             funcs->ba_print(stdout, pbooks, n_books);
//             funcs->ba_sort(pbooks, n_books, book_cmp_by_title);
//             funcs->ba_print(stdout, pbooks, n_books);
//             funcs->ba_free(pbooks, n_books);
//         }
//         fclose(f);
//     }
//     else
//         rc = ERR_IO;
    
//     return rc;
// }

// int lib_load_funcs(void *hlib, struct lib_funcs_t *funcs)
// {
//     funcs->ba_create = dlsym(hlib, "ba_create");
//     if (!funcs->ba_create)
//     {
//         fprintf(stderr, "Can not load lib: %s\n", dlerror());
//         return ERROR_IMPORT_FUNC;
//     }
//     funcs->ba_free = dlsym(hlib, "ba_free");
//     if (!funcs->ba_free)
//     {
//         fprintf(stderr, "Can not load lib: %s\n", dlerror());
//         return ERROR_IMPORT_FUNC;
//     }
//     funcs->ba_print = dlsym(hlib, "ba_print");
//     if (!funcs->ba_print)
//     {
//         fprintf(stderr, "Can not load lib: %s\n", dlerror());
//         return ERROR_IMPORT_FUNC;
//     }
//     funcs->ba_sort= dlsym(hlib, "ba_sort");
//     if (!funcs->ba_sort)
//     {
//         fprintf(stderr, "Can not load lib: %s\n", dlerror());
//         return ERROR_IMPORT_FUNC;
//     }
//     return EXIT_SUCCESS;
// }
