#include "libmy.h"


int list_init(size_t maxsize, node_t **head, int *array, size_t *size)
{
    size_t counter = 0;
    char choose = '1';
    while ((choose == '1') && (counter < maxsize))
    {
        int tmp_i;
        printf("Осталось ввести [%ld] - чисел\n>>", maxsize - counter);
        if ((fscanf(stdin, "%d", &tmp_i)) != 1)
        {
            printf("Ошибка считывания числа\n");
            return ERR_NUM_INPUT;
        }
        node_t *tmp = node_create(tmp_i);
        if (!tmp)
        {
            printf("Ошибка выделения памяти при создании узла списка\n");
            return ERR_MEM;
        }
        *head = add(tmp, *head);
        array[*size] = tmp_i;
        (*size)++;
        counter ++;
        if (counter >= maxsize)
        {
            printf("Вы ввели максимальное количество чисел в список\nЗавершаю.....\n");
            return ERR_OK;
        }
        printf("Желаете продолжить ?\n\t1 - Да\n\tДругое - Нет\n>>");
        fscanf(stdin, " %c", &choose);
        scanf("%*[^\n]");
    }
    return ERR_OK;
}

int list_init_random(size_t maxsize, node_t **head, int *array, size_t *size)
{
    size_t counter = 0;
    while (counter < maxsize)
    {
        int tmp_i;
        tmp_i = rand() % 10000;
        node_t *tmp = node_create(tmp_i);
        if (!tmp)
        {
            printf("Ошибка выделения памяти при создании узла списка\n");
            return ERR_MEM;
        }
        *head = add(tmp, *head);
        array[*size] = tmp_i;
        (*size)++;
        counter ++;
        if (counter >= maxsize)
        {
            // printf("Вы ввели максимальное количество чисел в список\nЗавершаю.....\n");
            // print_a(array, *size);
            return ERR_OK;
        }
    }
    return ERR_OK;
}

node_t *node_create(int item)
{
    node_t *new = malloc(sizeof(node_t));
    if (new)
    {
        new->item = item;
        new->next = NULL;
    }
    return new;
}

pointer_t *pointer_create(node_t *tmp)
{
    pointer_t *new = malloc(sizeof(pointer_t));
    if (new)
    {
        new->next_node = tmp;
        new->next_pointer = NULL;
    }
    return new;
}

node_t *add(node_t *node, node_t *head)
{
    node->next = head;
    return node;
}


pointer_t *add_pointer(pointer_t *node, pointer_t *head)
{
    node->next_pointer = head;
    return node;
}


void clear_node(node_t **tmp)
{
    node_t *tmp_node = *tmp;
    *tmp = (*tmp)->next;
    free(tmp_node);
}

void clear(node_t *head)
{
    node_t *tmp = head;
    while (head)
    {
        tmp = head->next;
        free(head);
        head = tmp;
    }
}

void add_back(node_t *head, node_t *node)
{   
    node_t *tmp = head;
    for (; tmp->next; tmp = tmp->next);
    tmp->next = node;
}
