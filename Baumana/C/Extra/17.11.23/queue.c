#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "queue.h"


queue_t queue_create(void)
{
    // q or *q
    queue_t q = malloc(sizeof(struct queue_type));
    if (!q)
    {
        return NULL;
    } 

    q->head = NULL;
    q->tail = NULL; 
    return q;
}



struct node_t *node_create(int item)
{
    struct node_t *node = malloc(sizeof(struct node_t));
    if (node)
    {
        node->next = NULL;
        node->item = item;
    }
    return node;
}


void node_free(struct node_t *node)
{
    free(node);
}


bool queue_is_empty(const queue_t q)
{
    assert(q);
    return ((q->head == NULL)  && (q->tail ==NULL));
}


bool queue_is_full(const queue_t q)
{
    assert(q);
    return false;
}


int queue_push(queue_t q, int item)
{
    if (queue_is_full(q))
    {
        return 1;
    }
    
    struct node_t *new_elem = node_create(item);
    
    if (!new_elem)
    {
        return 4;
    }

    if (queue_is_empty(q))
    {
        q->head = new_elem;
        q->tail = new_elem;
    }
    else
    {
        q->tail->next = new_elem;
        q->tail = new_elem;
    }

    return 0;
}


int queue_pop(queue_t q, int *item)
{
    if (queue_is_empty(q))
        return 1;
    
    // struct node_t *new_elem = node_create(*item);
    
    struct node_t *new_elem = q->head;

    q->head = q->head->next;
    if (q->head == NULL)
    {
        q->tail = NULL;
    }
    *item = new_elem->item;
    
    node_free(new_elem);
    
    return 0;
}


void queue_destroy(queue_t q)
{
    assert(q);
    int item;
    while (!queue_is_empty(q))
    {
        queue_pop(q, &item);
    }    
    free(q);
}
