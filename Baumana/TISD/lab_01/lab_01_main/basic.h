#ifndef BASIC_H_
#define BASIC_H_

#include "libmy.h"

#define ARR 100

int multiply(int *arr_m, size_t size_m, int *arr_n, size_t size_n, int *order, char flag);


int change_order(int *arr, size_t arr_size);


int mass_summa(int arr[ARR][ARR], size_t *row, size_t *column);


int normalized_number(char *mantissa, int *order, size_t *point_position);


int base(struct long_number_t *number);


int from_char_to_int(char *arr, size_t arr_len, int *number, size_t *size);


void print_arr(int *arr, int size);


int left_shift(int *arr, size_t size, int *order);


#endif // BASIC_H_