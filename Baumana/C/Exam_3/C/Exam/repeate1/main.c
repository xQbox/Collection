#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node_t node_t;

struct node_t
{
    int arr[2];
    node_t *next;
};

node_t *create_node(char *buf)
{
    if (!buf)
        return NULL;
    int a,b;
    char end;
    if ((sscanf(buf, "%d %d%c", &a, &b, &end)) != 3)
    {
        free(buf);
        return NULL;
    }
    if (end != '\n')
    {
        free(buf);
        return NULL;
    }
    node_t *tmp = malloc(sizeof(node_t));
    if (!tmp)
    {
        free(buf);
        return NULL;
    }
    tmp->arr[0] = a;
    tmp->arr[1] = b;
    tmp->next = NULL;
    return tmp;
}

node_t *add(node_t *head, node_t *node)
{
    if (!head)
        return node;
    node_t *tmp = head;
    while (tmp->next) tmp = tmp->next;
    tmp->next = node;
    return head;
}

int input_line(node_t **head_n)
{
    ssize_t read;
    size_t count = 0;
    char *buf = NULL;
    node_t *head = NULL;
    while ((read = getline(&buf, &count, stdin)) != -1)
    {
        node_t *tmp = create_node(buf);
        if (!tmp)
            break;
        head = add(head, tmp);
        free(buf);
        buf = NULL;
        count = 0;
    }
    *head_n = head;
    return 0;
}

node_t *find(node_t *head)
{
    node_t *tmp = head;
    while (tmp)
    {
        if (tmp->arr[0] == tmp->arr[1])
            return tmp;
        tmp = tmp->next; 
    }
    return NULL;
}

node_t *create_list(node_t **head, node_t **new_list, node_t *find)
{
    if (*head == find)
    {
        *head = (*head)->next;
        find->next = NULL;
        *new_list = add(*new_list, find);
        return *head; 
    }
    node_t *tmp = *head;
    while (tmp->next != find) tmp = tmp->next;
    if (find->next == NULL)
    {
        tmp->next = NULL;
        *new_list = add(*new_list, find);
        return *head;
    }
    else 
    {
        tmp->next = find->next;
        find->next = NULL;
        *new_list = add(*new_list, find);
        return *head;
    }
}

node_t *exercise(node_t **head)
{
    node_t *tmp = *head;
    node_t *res = NULL;
    node_t *new_list = NULL;
    while ((res = find(tmp)))
    {
        tmp = create_list(head, &new_list, res);
    }
    return new_list;
}


void print_node(node_t *head)
{
    printf("%d %d\n", head->arr[0], head->arr[1]);
}

void print_list(node_t *head)
{
    node_t *tmp = head;
    while (tmp)
    {
        print_node(tmp);
        tmp = tmp->next;
    }
}

void free_node(node_t *head)
{
    free(head);
}

void free_list(node_t *head)
{
    while (head)
    {
        node_t *tmp = head;
        head = head->next;
        free_node(tmp);
    }
}

int main(void)
{
    node_t *head = NULL;
    int rc = 1;
    while ((rc = input_line(&head)) != 0);
    // print_list(head);
    node_t *new_list = exercise(&head);
    
    if (head)
    {
        print_list(head);
        free_list(head);
    }
    printf("\n\n\n");
    if (new_list)
    {
        print_list(new_list);
        free_list(new_list);
    }
    return 0;
}