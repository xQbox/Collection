#ifndef IO_H_
#define IO_H_

#include "libmy.h"

// Проверка файла
int file_check(char *filename);


// Считывание строки из файла
int read_string(FILE *fp , char *string);
// Считывание числа из файла
int read_number(FILE *fp, int *number);


// Вывод предмета
int print_subject(struct subject *items, size_t number);

#endif // IO_H_