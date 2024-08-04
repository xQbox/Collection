#ifndef MYERRORS_H_
#define MYERRORS_H_

#define ERR_OK 0              // Позитивный исход
#define ERR_IO 1              // Ошибка ввода
#define ERR_RANGE 2           // Ошибка диапазона
#define ERR_STAGEO 3
#define ERR_STAGET 4
#define ERR_STAGETH 5
#define ERR_STAGEF 7
#define ERR_STAGEFI 8
#define ERR_STAGESIX 9
#define ERR_STAGESEVEN 10
#define ERR_STAGEEIGH 15
#define ERR_STAGENINE 16
#define ERR_STAGETEN  17
#define ERR_STAGEELEVEN 18

#define ERR_OPEN_FILE 20
#define ERR_CLOSE_FILE 21
#define ERR_EMPTY_FILE 22

#define ERR_STRING 30
#define ERR_MAS    31
#define ERR_VOLUME 32
#define ERR_ENDSTRING 33
#define ERR_DATA 34

#define ERR_SUBSTRING 40

#define ERR_ARR_SIZE 11       // Ошибка неправильного размера функции-фильтра 
#define ERR_MEM 12            // Ошибка выделения памяти
#define ERR_SIZE 13           // Ошибка некорректного размера массива 

#define  ERR_ARG_BAD 14       // Ошибка невалидных входных данных командной строки

#endif // MYERRORS_H_