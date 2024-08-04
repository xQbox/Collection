#ifndef STRUCT_H_
#define STRUCT_H_

#include "libmy.h"

#define NAME_LEN 25 // Максимальное название предмета

struct items_t
{
    char name[NAME_LEN + 1];
    double mass;
    double amount;
};


#endif // STRUCT_H_