#ifndef NODE_H_
#define NODE_H_

#include "libmy.h"

struct node_t
{
    int item; // Числовые данные 
    struct node_t *next; // Указатель на следующий элемент списка
};

struct pointer_t
{
    struct node_t *next_node;
    struct pointer_t *next_pointer;
};

// struct stack_array_t
// {
//     int max_size; // Максимальный размер стека
//     int cur_pos; // Уровень заполненности
//     int *array; // Указатель на начало массива 
// }

typedef struct pointer_t pointer_t;

typedef struct node_t node_t;

node_t *add(node_t *node, node_t *head);

node_t *node_create(int item);

int list_init(size_t maxsize, node_t **head, int *array, size_t *size);

void clear_node(node_t **tmp);

int list_init_random(size_t maxsize, node_t **head, int *array, size_t *size);

void clear(node_t *head);


pointer_t *pointer_create(node_t *tmp);

pointer_t *add_pointer(pointer_t *node, pointer_t *head);

#endif // NODE_H_