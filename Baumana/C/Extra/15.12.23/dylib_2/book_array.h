#ifndef __BOOK_ARRAY_H__

#define __BOOK_ARRAY_H__


#include <stdio.h>
#include "error.h"
#include "book.h"


int ba_count(FILE *f, int *n);


int ba_read(FILE *f, struct book_t *pbooks, int n);


int ba_create(FILE *f, struct book_t **pbooks, int *n_books);


void ba_print(FILE *f, const struct book_t *pbooks, int n);


void ba_sort(struct book_t *pbooks, int n, int (*cmp)(const void*, const void*));


void ba_free(struct book_t *pbooks, int n);


#endif
