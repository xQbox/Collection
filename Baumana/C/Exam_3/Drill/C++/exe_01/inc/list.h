#ifndef LIST_H_
#define LIST_H_

typedef struct node_t node_t;

struct node_t 
{
    char action;
    node_t *next;
};

typedef struct nodeint_t nodeint_t;

struct nodeint_t
{
    int64_t number;
    nodeint_t *next;
};

typedef struct stack_t stack_t;

struct stack_t
{
    int16_t amount;  // заполненность стека
    node_t *head;    // указатель на голову данных 
};

void free_node(node_t *node);
char get_data_node(node_t *node);
void pop_node(node_t *node);
node_t *push_node(node_t *node, node_t *add);
node_t *create_node(char action);


int init_stack(stack_t **stack, node_t *head);
stack_t *push(stack_t *stack, char action);
stack_t *pop(stack_t *stack);
char get_stackdata(stack_t *stack);
void print_stack(stack_t *stack);

typedef struct stackint_t stackint_t;

struct stackint_t
{
    int16_t amount;  // заполненность стека
    nodeint_t *head;    // указатель на голову данных 
};


void free_nodeint(nodeint_t *node);
char get_data_nodeint(nodeint_t *node);
void pop_nodeint(nodeint_t *node);
nodeint_t *push_nodeint(nodeint_t *node, nodeint_t *add);
nodeint_t *create_nodeint(int64_t number);


int init_stackint(stack_t **stack, nodeint_t *head);
stackint_t *pushint(stackint_t *stack, int64_t number);
stackint_t *popint(stackint_t *stack);
int64_t get_stackintdata(stackint_t *stack);
void print_stackint(stackint_t *stack);


#endif // LIST_H_