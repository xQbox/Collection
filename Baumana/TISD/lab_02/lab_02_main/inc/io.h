#ifndef IO_H_
#define IO_H_
#include "libmy.h"


// Проверки
int file_check(char *filename);

int number_check(int *number);

// Считывание структуры
int data_read(struct data_t *data, FILE *f);

int duration_read(size_t *a, FILE *f);

int price_read(char *string, FILE *f);

int minage_read(size_t *a, FILE *f);

// Ввод данных
int line_read(char *string, FILE *f);

int number_read(int *a, FILE *f);

int line_input(char *string);

int price_input(char *string);

int number_input(int *number);

int duration_input(size_t *number);

int minage_input(size_t *number);

int input_delete_parameters(char *string);

// Вывод 
void print_table(struct data_t *data, int num);

void print_key_table(struct keys_t *data);

void menu_print();

void show_err_message(int rc);



#endif // IO_H_
