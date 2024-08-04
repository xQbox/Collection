#ifndef LIBMY_H_
#define LIBMY_H_

#include <stdio.h>
#include <string.h>

#include "struct.h"             // Информация о структурах
#include "io.h"                 // Ввод/Вывод/Проверки 
#include "construct.h"          // Основные функции работы с программой



#define ERR_OK 0                // Нет ошибок
#define ERR_BADPAR 1            // Ошибка невалидных аргументов командной строки
#define ERR_IO 2                // Ошибка ввода вывода данных
#define ERR_DATA 3              // Ошибка считывания данных

#define ERR_STR_OVERFLOW 4      // Ошибка переполнения предмета 
#define ERR_STRUCT_OVERFLOW 5   // Ошибка переполнения структур
#define ERR_NUM_OVERFLOW 6      // Ошибка переполнения числа
#define ERR_EMPTY_STRING 10     // Ошибка пустой строки

#define ERR_OPEN_FILE 7         // Ошибка открытия файла
#define ERR_EMPTY_FILE 8        // Ошибка пустой файл
#define ERR_CLOSE_FILE 9        // Ошибка закрытия файла


#endif // LIBMY_H_