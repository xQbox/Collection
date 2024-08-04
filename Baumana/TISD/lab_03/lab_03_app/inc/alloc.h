#ifndef ALLOC_H_
#define ALLOC_H_

#include "libmy.h"

int **matrix_alloc(size_t row, size_t col);

void matrix_free(int **ptr, size_t size);

#endif // ALLOC_H_