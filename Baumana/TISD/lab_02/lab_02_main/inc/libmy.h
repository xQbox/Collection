#ifndef LIBMY_H_
#define LIBMY_H_

                            /// постоянные        
#define PAUSE "read -p 'Нажмите Enter для продолжения...' var"
#define ARR_SIZE 40
#define STRING_SIZE 30
#define PRICE "^[0-9]{0,4}|10000$"
#define elements_count(a) ( sizeof(a) / sizeof(*(a)) )


                            /// дополнительные библиотеки 
#include <string.h>     
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "struct.h"          /// подключение структур
#include "myerrors.h"        /// декларация ошибок
#include "io.h"              /// функции ввода\вывода 
#include "basic.h"           /// основные функции программы




#endif //LIBMY_H_