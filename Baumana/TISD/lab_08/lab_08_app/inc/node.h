#ifndef NODE_H_
#define NODE_H_

node_t *create_node_dinamic(char *name, int cost);

node_t *create_node(char *name, int cost);

node_t *add_node(node_t *head, node_t *tmp);

dict_t *create_dict(node_t *head, node_t *tail, size_t pos);

void node_free(node_t *tmp);

void list_clear(node_t *head);

void matrix_free(int **matrix, size_t n);

#endif //NODE_H_