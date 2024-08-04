#include "libmy.h"

/*  Блок работа со списком char'ов (push инициализирует пустой список)*/
void free_node(node_t *node)
{
    free(node);
}

char get_data_node(node_t *node)
{
    return node->action;    
}

void pop_node(node_t *node)
{
    if (!node)
        return;

    node_t *tmp = node;
    node_t *prev = node;
    while (tmp->next != NULL) 
    {
        prev = tmp;
        tmp = tmp->next;
    }
    prev->next = NULL;    
    free_node(node);
}

node_t *push_node(node_t *node, node_t *add)
{
    if (!node)
        return add;
    
    node_t *tmp = node;
    while (tmp->next != NULL) tmp = tmp->next;
    tmp->next = add;

    return node;
}

node_t *create_node(char action)
{
    node_t *tmp = (node_t *)malloc(sizeof(node_t));
    if (!tmp)
        return NULL;
    tmp->action = action;
    tmp->next = NULL;
    return tmp;
}


/*  Блок работы со стеком */

// говнокод переделать
int init_stack(stack_t **stack, node_t *head)
{ 
    if (!head)
        return 1;

    node_t *tmp = (node_t *) head;
    int16_t count = 0;
    while (tmp->next != NULL) 
    {
        tmp = tmp->next;
        ++count;
    }
    *stack = (stack_t *)malloc(sizeof(stack_t));
    (*stack)->amount = count;
    (*stack)->head = tmp;
    return 0;
}

stack_t *push(stack_t *stack, char action)
{
    if (!stack)
    {
        // std::cout << "Инициализация стека\n";
        
        stack_t *stmp = (stack_t *) malloc(sizeof(stack_t));
        if (!stmp)
            return NULL;
        
        node_t *tmp = create_node(action);
        if (!tmp)
        {
            free(stmp);
            return NULL;
        }
        stmp->amount = 1;
        stmp->head = tmp;
        stmp->head->action = action;
        stack = stmp;

        return stack;
    }
    node_t *tmp = create_node(action);
    if (!tmp)
    {
        std::cout << "Неудачное выделение памяти\n";
        return NULL;
    }
    tmp->next = stack->head;
    stack->head = tmp;
    stack->amount += 1;
    return stack;
}

stack_t *pop(stack_t *stack)
{
    if (!stack)
        return NULL;

    if (stack->amount == 0)
    {
        // std::cout << "Стек пуст\n";
        return NULL;
    }
    node_t *tmp = stack->head;
    stack->head = stack->head->next;
    stack->amount -= 1;
    free_node(tmp);
    return stack;
}

char get_stackdata(stack_t *stack)
{
    if (!stack)
        return '0';

    if (stack->amount == 0)
    {
        // std::cout << "Стек пуст\n";
        return '0';
    }
    return stack->head->action;
}

void print_node(node_t *node)
{
    std::cout << node->action << '\n';
}

void print_stack(stack_t *stack)
{
    if (!stack)
        return ;
    node_t *tmp = stack->head;
    while (tmp != NULL) 
    {
        print_node(tmp);
        tmp = tmp->next;
    }
}









/*  Блок работа со списком char'ов (push инициализирует пустой список)*/
void free_nodeint(nodeint_t *node)
{
    free(node);
}

char get_data_nodeint(nodeint_t *node)
{
    return node->number;    
}

void pop_nodeint(nodeint_t *node)
{
    if (!node)
        return;

    nodeint_t *tmp = node;
    nodeint_t *prev = node;
    while (tmp->next != NULL) 
    {
        prev = tmp;
        tmp = tmp->next;
    }
    prev->next = NULL;    
    free_nodeint(node);
}

nodeint_t *push_nodeint(nodeint_t *node, nodeint_t *add)
{
    if (!node)
        return add;
    
    nodeint_t *tmp = node;
    while (tmp->next != NULL) tmp = tmp->next;
    tmp->next = add;

    return node;
}

nodeint_t *create_nodeint(int64_t number)
{
    nodeint_t *tmp = (nodeint_t *)malloc(sizeof(nodeint_t));
    if (!tmp)
        return NULL;
    tmp->number = number;
    tmp->next = NULL;
    return tmp;
}



/*  Блок работы со стеком */

// говнокод переделать
int init_stackint(stackint_t **stack, nodeint_t *head)
{ 
    if (!head)
        return 1;

    nodeint_t *tmp = (nodeint_t *) head;
    int16_t count = 0;
    while (tmp->next != NULL) 
    {
        tmp = tmp->next;
        ++count;
    }
    *stack = (stackint_t *)malloc(sizeof(stackint_t));
    (*stack)->amount = count;
    (*stack)->head = tmp;
    return 0;
}

stackint_t *pushint(stackint_t *stack, int64_t number)
{
    if (!stack)
    {
        // std::cout << "Инициализация стека\n";
        stackint_t *stmp = (stackint_t *) malloc(sizeof(stackint_t)); 
        if (!stmp)
            return NULL;
        nodeint_t *tmp = create_nodeint(number);
        if (!tmp)
        {
            free(stmp);
            return NULL;
        }
        stmp->amount = 1;
        stmp->head = tmp;
        stmp->head->number = number;
        stack = stmp;
        return stack;
    }
    nodeint_t *tmp = create_nodeint(number);
    if (!tmp)
    {
        std::cout << "Неудачное выделение памяти\n";
        return NULL;
    }
    tmp->next = stack->head;
    stack->head = tmp;
    stack->amount += 1;
    return stack;
}

stackint_t *popint(stackint_t *stack)
{
    if (!stack)
        return NULL;
    if (stack->amount == 0)
    {
        // std::cout << "Стек пуст\n";
        return NULL;
    }
    nodeint_t *tmp = stack->head;
    stack->head = stack->head->next;
    stack->amount -= 1;
    free_nodeint(tmp);
    return stack;
}

int64_t get_stackintdata(stackint_t *stack)
{
    if (!stack)
        return -1; // todo

    if (stack->amount == 0)
    {
        // std::cout << "Стек пуст\n";
        return -1; // todo
    }
    return stack->head->number;
}


void print_nodeint(nodeint_t *node)
{
    std::cout << node->number << '\n';
}

void print_stackint(stackint_t *stack)
{
    if (!stack)
        return ;
    nodeint_t *tmp = stack->head;
    while (tmp != NULL) 
    {
        print_nodeint(tmp);
        tmp = tmp->next;
    }
}
