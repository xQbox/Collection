#ifndef CONSTRUCT_H_
#define CONSTRUCT_H_

#include "libmy.h"

// Проверка параметров командной строки
int check_the_par (char *line);

// Сортировка элементов массива структур от наименьшей плотности к наибольшей
int lowdens_to_highdens_sort();

// Вывод всей информации из файла
int all_sort();

// Поиск по подстроке в файле 
int substring_sort();

// Печать ошибок в соответствии с номером
void show_err_message(int rc);

#endif // CONSTRUCT_H