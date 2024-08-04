#ifndef __MTR_IO_H__

#define __MTR_IO_H__

#include <stdio.h>
#include <stdlib.h>
#include "mtr_errors.h"


int matrix_read(FILE *f, double **data, size_t n, size_t m);


int matrix_create(FILE *f, double ***data, size_t *n, size_t *m);


int matrix_create_ex(const char *fname, double ***data, size_t *n, size_t *m);


int matrix_print(double **a, size_t n, size_t m);


#endif
