#ifndef NODE_H_
#define NODE_H_

typedef struct node_t node_t; 

struct node_t 
{
    char *surname;
    int year;
    char *group;
    node_t *next; 
};

node_t *push_out(node_t *head, node_t *node);
node_t *push(node_t *head, node_t *node);
node_t *create(char *surname, int year, char *group);
void free_node(node_t *node);
void free_list(node_t *head);
node_t **list_create();
void list_free(node_t *head);
void list(node_t *head);


#endif // NODE_H_