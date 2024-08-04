#ifndef IO_H_
#define IO_H_

#include "libmy.h"

int number_sec_check(size_t *number, size_t param);

int number_check(int *number);

int matrix_more_input(int **ptr, size_t row, size_t col, size_t sparse_percentage, size_t *count_of_values);

int matrix_less_input(int **ptr, size_t row, size_t col, size_t sparse_percantage, size_t *count_of_values);

int matrix_input(int **ptr, size_t row, size_t col, int *ptrd, size_t *index);

void matrix_print(int **ptr, size_t row, size_t col);

int matrix_size_input(size_t *row, size_t *col);

void array_print(int *ptr, size_t size);

void structur_vector_input(int *ptr_vector, size_t vector_size, int *vector_values, int *vector_position, int *pointer_vector);

int vector_input(int *ptr, size_t size, size_t *counter, size_t percentage);

void random_vector_input(int *ptr, size_t size, size_t *counter, size_t percentage);

#endif // IO_H_
