#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdbool.h>
#include <stdio.h>

struct node_t 
{
    int item;
    struct node_t *next;
};

struct queue_type
{
    struct node_t *head;
    struct node_t *tail;
};

typedef struct queue_type* queue_t;

queue_t queue_create(void);

void queue_destroy(queue_t q);

bool queue_is_empty(const queue_t q);

void node_free(struct node_t *node);

struct node_t *node_create(int item);

bool queue_is_full(const queue_t q);

int queue_push(queue_t q, int item);

int queue_pop(queue_t q, int *item);


#endif // QUEUE_H_