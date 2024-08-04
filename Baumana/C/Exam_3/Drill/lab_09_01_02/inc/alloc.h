#ifndef ALLOC_H_
#define ALLOC_H_

struct item_t *arr_create(size_t size, struct item_t *item);

void arr_free(struct item_t *item);

void item_free(struct item_t *ptr);

void ai_free(struct item_t *ptr, size_t size);

#endif // ALLOC_H_