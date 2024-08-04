#ifndef MTR_ALLOC_H__

#define MTR_ALLOC_H__


#include <stdlib.h>
#include "mtr_errors.h"


void matrix_free(double **data, size_t n);


double** matrix_alloc(size_t n, size_t m);

// столбец
int matrix_del_column(double **data, size_t n, size_t *m, size_t j);

// строка . *** используется потому что изменяется количество строк в массиве указателей
int matrix_del_row(double ***data, size_t *n, size_t m, size_t i);


#endif

