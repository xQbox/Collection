#ifndef __BOOK_H__

#define __BOOK_H__


#include <stdio.h>
#include "error.h"


struct book_t
{
    char *title;
    int  year;
};


int book_init(struct book_t *pbook, const char *title, int year);


int book_copy(struct book_t *pdst, const struct book_t *psrc);


void book_free_content(struct book_t *pbook);


int book_read(FILE *f, struct book_t *pbook);


int book_read_ex(FILE *f, struct book_t *pbook);


void book_print(FILE *f, const struct book_t *pbook);


int book_cmp_by_title(const void *l, const void *r);


int book_cmp_by_year(const void *l, const void *r);


#endif