#ifndef NODE_H_
#define NODE_H_


typedef struct node_t node_t;
// развернутый односвязный список  
struct node_t
{
    int arr[2];
    node_t *next;
};

node_t *create_node(char *buf);

node_t *add(node_t *head, node_t *node);
node_t *push(node_t *head, node_t *node);

node_t *find_node(node_t *head, int (*comp)(node_t *));

node_t *remove_node(node_t **head, node_t *find);

void print_list(node_t *head);
void print_node(node_t *head);

void free_node(node_t *head);
void free_list(node_t *head);

int create_list(node_t **head_n);

int comp_node(node_t *node);

#endif // NODE_H_