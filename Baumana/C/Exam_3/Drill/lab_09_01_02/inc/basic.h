#ifndef BASIC_H_
#define BASIC_H_

int ai_init(char *filename, size_t *size, struct item_t **ptr);

void buble_sort(struct item_t *ptr, size_t size, int (*comp)(double left, double right));

int comp(double left, double right);

void swap(struct item_t *left, struct item_t *right);

int substring_find(char *substring, struct item_t *ptr, size_t size);

void sort(struct item_t *ptr, size_t size);

int ai_create(char *filename, size_t size, struct item_t *ptr);


int substring_collect(char *substring, char *item_name);

#endif // BASIC_H_