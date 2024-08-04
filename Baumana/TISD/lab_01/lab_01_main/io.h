#ifndef IO_H_
#define IO_H_

#include "libmy.h"


int number_input(char *number);


int mantissa_input(char *mantissa, size_t *point_position);


int order_input(int *order);


int sign_input(char *sign);


int struct_input(struct long_number_t *number);


void show_err_message(int rc);


#endif // IO_H_