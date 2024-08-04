#include "libmy.h"

node_t *create_node_dinamic(char *name, int cost)
{
    node_t *tmp = malloc(sizeof(node_t));
    if (!tmp)
        return NULL;
    char *vertex =  (char *) malloc(strlen(name) + 1);
    if (!vertex)
    {
        free(tmp);
        return NULL;
    }
    free(vertex);
    strcpy(vertex, name);
    printf("%s\n", vertex);
    tmp->vertex_name = vertex;
    tmp->next = NULL;
    tmp->way_cost = cost;
    return tmp;
}

node_t *create_node(char *name, int cost)
{

    node_t *tmp = malloc(sizeof(node_t));
    if (!tmp)
        return NULL;
    
    char *tmp_name = malloc(strlen(name) + 1);
    
    if (!tmp_name)
    {
        free(tmp);
        return NULL;
    }
    strcpy(tmp_name, name);
    tmp->vertex_name = tmp_name;
    tmp->next = NULL;
    tmp->way_cost = cost;
    return tmp; 
}

node_t *add_node(node_t *head, node_t *tmp)
{
    node_t *tmp_e = head;
    while (tmp_e->next)
    {
        tmp_e = tmp_e->next;
    }
    tmp_e->next = tmp;
    return head;
}

dict_t *create_dict(node_t *head, node_t *tail, size_t pos)
{
    dict_t *dict = malloc(sizeof(dict_t));
    char *tmp_name = malloc(strlen(head->vertex_name) + 1);
    
    if (!dict)
        return NULL;
    
    if (!tmp_name)
    {
        free(dict);
        return NULL;
    }

    dict->head = head;
    dict->tail = tail;
    
    strcpy(tmp_name, head->vertex_name);
    dict->vertex_name = tmp_name;
    dict->i = pos;
    return dict; 
}

void node_free(node_t *tmp)
{
    if (tmp)
    {
        free(tmp->vertex_name);
        free(tmp);
    }
}

void list_clear(node_t *head)
{
    node_t *tmp = head;
    while (tmp)
    {
        tmp = tmp->next;
        node_free(head);
        head = tmp;
    }
}

void matrix_free(int **matrix, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        free(matrix[i]);
    }
    free(matrix);
}
