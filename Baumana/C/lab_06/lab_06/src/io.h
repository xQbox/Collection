#ifndef _IO_H_
#define _IO_H_

#include "libmy.h"

// Проверка файла
int file_check(char *filename);

// Считывания строки из файла
int read_string(FILE *fp , char *string);
// Считывание структуры из файла
int read_struct(FILE *fp, char *name, double *mass, double *amount);

// Вывод предмета
int print_subject(struct items_t *items, size_t number);

#endif // _IO_H_