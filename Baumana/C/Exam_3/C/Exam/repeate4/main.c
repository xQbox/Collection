#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node_t node_t;

struct node_t
{
    int arr[3];
    node_t *next;
};

node_t *add(node_t *head, node_t *node)
{
    if (!head)
    {
        return node;
    }
    node_t *tmp = head;
    while (tmp->next) tmp = tmp->next;
    tmp->next = node;
    return head;
}


node_t *create_node(char *buf)
{
    if (!buf)
    {
        return NULL;
    }
    int a, b, c;
    char end;
    if ((sscanf(buf, "%d %d %d%c", &a, &b, &c, &end)) != 4)
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
    tmp->arr[2] = c;
    tmp->next = NULL;
    return tmp;
}

int input_line(node_t **head_n)
{
    ssize_t read;
    size_t count = 0;
    char *buf = NULL;
    node_t *head  = NULL;
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
        if (tmp->arr[1] < 0 || tmp->arr[2] < 0)
        {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

void free_node(node_t *head)
{
    free(head);
}

node_t *change_pos(node_t **head, node_t *find)
{
    if (*head == find)
    {
        if (find->next == NULL)
        {
            free_node(find);
            *head = NULL;
            return *head;
        }
        else 
        {
            *head = (*head)->next;
            free_node(find);
            return *head;
        }
    }
    node_t *tmp = *head;
    while (tmp->next != find) tmp = tmp->next;
    if (find->next == NULL)
    {
        tmp->next = NULL;
        free_node(find);
        return *head;
    }
    else 
    {
        tmp->next = find->next;
        free_node(find);
        return *head;
    }
}


node_t *exercise(node_t **head)
{
    node_t *tmp = *head;
    node_t *res = NULL;
    while ((res = find(tmp)))
    {
        tmp = change_pos(head, res);
    }
    return *head;
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

void print_node(node_t *head)
{
    printf("%d %d %d\n", head->arr[0], head->arr[1], head->arr[2]);
}

void print_list(node_t *head)
{
    node_t *tmp = head;
    while (tmp)
    {
        print_node(tmp);
        tmp=tmp->next;
    }
}

int main(void)
{
    int rc = 1;
    node_t *head = NULL;
    while ((rc = input_line(&head)) != 0);
    if (!head)
    {
        return 2;
    }
    print_list(head);
    printf("\n\n\n");
    head = exercise(&head);
    if (!head)
    {
        return 2;
    }
    print_list(head);
    free_list(head);
    return rc;
}