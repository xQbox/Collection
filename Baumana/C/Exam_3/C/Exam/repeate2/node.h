#ifndef NODE_H_
#define NODE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node_t node_t;

struct node_t
{
    int arr[3];
    node_t *next;
};

node_t *create_node(char *buf);

node_t *add(node_t *head, node_t *node);

node_t *find(node_t *head);

node_t *change_pos(node_t **head, node_t **new_list, node_t *find);

int input_line(node_t **head_n);

node_t *exercise(node_t **head);

void print_node(node_t *head);

void print_list(node_t *head);

void free_node(node_t *head);

void free_list(node_t *head);

#endif // NODE_H_