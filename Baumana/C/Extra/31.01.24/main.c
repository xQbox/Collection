#include <stdio.h>
#include <stdlib.h>
#define list_entry(ptr, type, member) \
        ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

typedef struct lnode_t lnode_t;
struct lnode_t
{
    lnode_t *prev; 
    lnode_t *next;
};

typedef struct data_t data_t;
struct data_t 
{
    int id;
    lnode_t list;
    int pos;
}; 

lnode_t *create_list()
{
    lnode_t *tmp = malloc(sizeof(lnode_t ));
    if (!tmp)
        return NULL;
    tmp->next = NULL;
    tmp->prev = NULL; 
    return tmp;
}

lnode_t *add(lnode_t *head, lnode_t *node)
{
    if (!head)
        return node;
    lnode_t *tmp = head;
    while (tmp->next) tmp = tmp->next;
    tmp->next = node;
    node->prev = tmp;
    return head;
}


data_t *create_data(char *buf)
{
    if (!buf)
        return NULL;
    int a, b;
    char end;
    if ((sscanf(buf,"%d %d%c", &a, &b, &end)) != 3)
    {
        free(buf);
        return NULL;
    }
    if (end != '\n')
    {
        free(buf);
        return NULL;
    }
    data_t *tmp = malloc(sizeof(data_t));
    if (!tmp)
    {
        free(buf);
        return NULL;
    }
    tmp->id = a;
    tmp->pos = b;
    return tmp;
}

lnode_t *make_cirle(lnode_t *head)
{
    lnode_t *tmp = head;
    while (tmp->next) tmp = tmp->next;
    tmp->next = head;
    head->prev = tmp;
    return head;
}
// void print_list(lnode_t *head)
// {
//     if 
// }

int input_line(data_t **head_n, lnode_t **list)
{
    ssize_t read;
    size_t count = 0;
    char *buf = NULL;
    lnode_t *head = NULL;
    while ((read = getline(&buf, &count, stdin)) != -1)
    {
        data_t *tmp = create_data(buf);
        
        if (!tmp)
            break;
        head = add(head, &tmp->list);    
        free(buf);
        buf = NULL;
        count = 0;
    }
    printf("ok\n");
    head = make_cirle(head);
    data_t *new = list_entry(head, data_t, list);
    *list = head;
    *head_n = new;
    return 0;
}


int main(void)
{
    data_t *head = NULL;
    lnode_t *list_n = NULL;
    int rc = 1;
    while ((rc = input_line(&head, &list_n)) != 0);

    lnode_t *tmp = list_n;
    do
    {
        data_t *new = list_entry(tmp, data_t, list);
        printf("%d %d\n", new->id, new->pos);
        tmp = tmp->next;
    }
    while (tmp != list_n);
    return 0;
}