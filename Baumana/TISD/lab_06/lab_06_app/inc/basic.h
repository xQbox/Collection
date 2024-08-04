#ifndef BASIC_H_
#define  BASIC_H_

#include "libmy.h"

void buble_sort(void *ptr, size_t amount, size_t size_elem, int (*comp) (const void *left, const void *right));
 
int comp(const void *left , const void *right); 

void swap(void *left, void *right, size_t size_elem);

void change(char *symbol);

int binar_search(int *arr, size_t k, int value, int *flag);

void treeprint(tree_t *tree);

#endif /// BASIC_H_