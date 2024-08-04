#ifndef BASIC_H_
#define BASIC_H_

#include "libmy.h"


node_t *towers(node_t *head_first, node_t *head_second, node_t *head_third);

void tower_a(int *a_first, size_t *i, int *a_second, size_t *j, int *a_third, size_t *k);

int check_number(size_t *number);

void make_choose(char *choose);

void second(int *a_first, size_t i, int *a_second, size_t j, node_t *head_first, node_t *head_second);

// int third(node_t **head_first, node_t **head_second, int *a_first, size_t *i, int *a_second, size_t *j, size_t maxim);


int third(node_t **head_first, node_t **head_second, int *a_first, size_t *i, int *a_second, size_t *j, size_t maxim, pointer_t **head_free, pointer_t **head_add);

void forth(size_t i, size_t j, size_t maxim);

void fifth(int *a_first, size_t i, int *a_second, size_t j, size_t maxim, pointer_t *head_free, pointer_t *head_first);

void sixth(int *a_first, size_t *i,int *a_second, size_t *j);

// int third(node_t **head_first, node_t **head_second, int *a_first, size_t *i, int *a_second, size_t *j, size_t maxim, int *a_add, size_t *l, int *a_free, size_t *m);

// void fifth(int *a_first, size_t i, int *a_second, size_t j, size_t maxim, int *a_add, size_t *l, int *a_free, size_t *m);

#endif // BASIC_H_