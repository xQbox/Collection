#ifndef LAB_08_BASIC_H_
#define LAB_08_BASIC_H_

#include "libmy.h"
void col_change(int **ptr, size_t *col, size_t row, size_t pos_col);

void swap(void *ptrl, void *ptrr, size_t elem_size);

void row_change(int **ptr, size_t *row, size_t pos_row);

int **matrix_add(int **ptr, size_t *row, size_t *col, size_t expected_size);

void max_find(int **ptr, size_t row, size_t col, size_t *max_row, size_t *max_col);

int **matrix_multi(int **ptra, int **ptrb, size_t row);

int **multiply(int **ptra, int **ptrb, size_t row, size_t expected);

int **matrix_resize(int **ptr, size_t *row, size_t *col, size_t expected_size);

int **matrix_sum_line(int **ptra, int **ptrb, size_t row);

int **matrix_one(size_t row);

#endif // LAB_08_BASIC_H_