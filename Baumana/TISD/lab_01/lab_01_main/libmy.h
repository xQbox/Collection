#ifndef LIBMY_H_
#define LIBMY_H_




#define MAX(a,b) (((a)>(b)?(a):(b)))
#define MIN(a,b) (((a)<(b)?(a):(b)))
#define ARR_LEN 40

#define ERR_OK 0              // Позитивный исход
#define ERR_POINT 13          // Позитивный исход с точкой
#define ERR_BADPAR 1          // Ошибка невалидных аргументов командой строки
#define ERR_MANT_IO 2         // Ошибка ввода мантиссы
#define ERR_IO 12             // Ошибка ввода данных
#define ERR_RANGE 3           // Ошибка диапозона значений
#define ERR_DATA 4            // Ошибка данных
#define ERR_OVERFLOW 5        // Ошибка переполнения массива структур
#define ERR_NUMBER 14         // Ошибка невалидного ввода номера

#define ERR_OPEN_FILE 6       // Ошибка открытия файла
#define ERR_DATA_FILE 7       // Ошибка некорректного файла
#define ERR_CLOSE_FILE 8      // Ошибка закрытия файла
#define ERR_EMPTY_FILE 10     // Ошибка пустой файл

#define ERR_EMPTY_STRING 9    // Ошибка считывания пустой строки
#define ERR_EOF 11            // Ошибка fgets при конце файла

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "struct.h"           // Подключение структур
#include "basic.h"            // Основные функции для работы программы
#include "io.h"               // Подключение ввода / вывода
#include "io_tests.h"         // Модульные тесты

#endif // LIBMY_H_