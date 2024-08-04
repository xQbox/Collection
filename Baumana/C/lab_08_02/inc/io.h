#ifndef LAB_08_IO_H_
#define  LAB_08_IO_H_
#include "libmy.h"
/// Проверяет файл на корректность данных (открытие, чтение , закрытие)
/// Подсчет количества интовских элементов в файле

int number_check(size_t *number);

int input(int *data);

int matrix_data(int **ptr, size_t row, size_t col);

void matrix_print(int **ptr, size_t row, size_t col);

int **create_matrix(int **ptr, size_t row);

int input_size(size_t *data);

#endif // LAB_08_IO_H_