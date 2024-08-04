#ifndef BASIC_H_
#define BASIC_H_

#include "libmy.h"
#define ARR_LEN 41
#define ARR 100
int multiply(int *arr, size_t size_arr, int *arr1, size_t size_arr1);

int change_order(int *arr, size_t arr_size);

int mass_summ(int arr[ARR][ARR], size_t *row, size_t *column);


int from_char_to_int(char *arr, size_t arr_len, int *arr_int, size_t *arr_int_len);

#endif // BASIC_H_