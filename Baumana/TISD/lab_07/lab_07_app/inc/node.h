#ifndef NODE_H_
#define NODE_H_



typedef struct node_t node_t;

struct node_t 
{
    char *word; // слово
    int count; // количество повторений слова
    node_t *next; // Указатель на следующий 
};



node_t *node_push(node_t *head, node_t *node);
node_t *node_create(char *word);
node_t *node_find(node_t *head, char *name, int *count);
void node_clear(node_t *node);
void node_iter(node_t *head);
bool node_add_to_end(node_t *head, node_t *node);
node_t *node_find_int(node_t *head, char *word);
void list_clear(node_t *head);
node_t *remove_node_from_list(node_t *head, char *word);
void list_print(node_t *head);
void node_print(node_t *head);
void list_print_to_file(FILE *f, node_t *head);

#endif // NODE_H_