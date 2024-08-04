#include "libmy.h"


node_t *push(node_t *head, node_t *node)
{
    node->next = head;
    return node;
}

node_t *push_out(node_t *head, node_t *node)
{
    head->next = node;
    head = node;
    return head;
}

node_t *create(char *surname, int year, char *group)
{
    char *tmp = malloc(strlen(surname) + 1);
    if (!tmp)
    {
        return NULL;
    }
    strcpy(tmp, surname);
    char *tmp_group = malloc(strlen(group) + 1);
    if (!tmp_group)
    {
        free(tmp);
        return NULL;
    }
    strcpy(tmp_group, group);

    node_t *node = malloc(sizeof(node_t));
    if (!node)
    {
        free(tmp);
        free(tmp_group);
        return NULL;
    }
    node->surname= NULL;
    node->group = NULL;
    node->next = NULL;
    node->surname = tmp;
    node->year = year;
    node->group = tmp_group;
    return node;
}

void free_node(node_t *node)
{
    if (node)
    {
        free(node->group);
        free(node->surname);
        free(node); 
    }
}

void list(node_t *head)
{
    node_t *tmp = head;
    while (tmp)
    {
        printf("%s\n %d\n %s\n", tmp->surname, tmp->year, tmp->group);
        tmp = tmp->next;
    } 
}



void list_free(node_t *head)
{
    node_t *tmp = head;
    while (tmp)
    {
        tmp = tmp->next;
        // printf("%p", (void *) head);
        free_node(head);
        // printf("%p", (void *) head);
        head = tmp;
    }
}