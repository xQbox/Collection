#ifndef LAB_07_IO_H_
#define  LAB_07_IO_H_
#include "libmy.h"
/// Проверяет файл на корректность данных (открытие, чтение , закрытие)
/// Подсчет количества интовских элементов в файле
int file_check(char *filename, size_t *elem_count);

int arr_create(char *filename, int *ptrs);

void print_arr(int *ptrs, int *ptrend);

int file_write(char *filename, int *ptrs, int *pend);
#endif // LAB_07_IO_H_