#ifndef BASIC_H_
#define BASIC_H_

void matrix_p_init(int **ptr, size_t row, size_t col, int *ptrd, size_t *index);

int percent_read(size_t *percent, size_t row, size_t col);

size_t percent_count(size_t percent, size_t row, size_t col);


/// Функция производит инициализацию массива указателей на ненулевые элементы вектора
/// Принимает указатель на массив столбцов и его размер
/// Возвращает NULL - неудача , Указатель - удача
int *pointer_init(int *ptr, size_t size_p, size_t all_size);

void structur_init(int **ptr, size_t row, size_t col, int *a_values, int *a_pos_colum, int *a_pos_row);

int *multiply_matrix_and_column_vector(int *ptr_values, int *ptr_columns, int *ptr_row_pointers, size_t ptr_colum_size, int *vector_values, int *vector_index, int *res);

void random_input(int **ptr, size_t row, size_t col, size_t sparse_percentage, size_t *count_of_values);

int *multiply_matrix(int **ptr, size_t row, size_t col, int *ptr_v, int *res);

#endif // BASIC_H_