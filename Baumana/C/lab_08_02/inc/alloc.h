#ifndef LAB_08_ALLOC_H_
#define LAB_08_ALLOC_H_

/// очистка памяти от матрицы, как массива указателей на строки
void matrix_free(int **ptr, size_t row);


/// выделение памяти под матриц, как массив указателей
int **matrix_input(size_t row, size_t col);

#endif // LAB_08_ALLOC_H