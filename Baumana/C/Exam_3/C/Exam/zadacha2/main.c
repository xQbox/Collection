#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t node_t;

struct node_t
{
    int nmbr[3];
    node_t *next;
};

node_t *create_node(char *buf)
{
    if (!buf)
        return NULL;
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
        printf("Error\n");
        return NULL;
    }
    tmp->nmbr[0] = a;
    tmp->nmbr[1] = b;
    tmp->nmbr[2] = c;
    tmp->next = NULL;
    return tmp;
}

node_t *add(node_t *head, node_t *node)
{
    if (head == NULL)
    {
        return node;
    }
    node_t *tmp = head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
    return head;
}

void print_node(node_t *tmp)
{
    printf("%d %d %d\n", tmp->nmbr[0], tmp->nmbr[1], tmp->nmbr[2]);
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

node_t *find(node_t *head)
{
    node_t *tmp = head;
    while (tmp)
    {
        if (tmp->nmbr[1] == tmp->nmbr[2])
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

node_t *change_pos(node_t **head, node_t *search)
{
    if (*head == search)
    {
        return *head;
    }
    node_t *tmp = *head;
    while (tmp->next != search)
        tmp = tmp->next;

    if (search->next == NULL)
    {
        tmp->next = NULL;
        search->next = *head;
        *head = search;
        return *head;
    }
    else
    {
        tmp->next = search->next;
        search->next = *head;
        *head = search;
        return *head;
    }
}

node_t *exercise(node_t **head)
{
    node_t *tmp = *head;
    node_t *res = NULL;
    while ((res = find(tmp)))
    {
        tmp = tmp->next;
        *head = change_pos(head, res);
    }
    return *head;
}

void free_list(node_t *head)
{
    while (head)
    {
        node_t *tmp = head;
        head = head->next;
        free(tmp);
    }
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
        count = 0;
        buf = NULL;
    }
    *head_n = head;
    return 0;
}

int main(void)
{
    node_t *head = NULL;
    int rc = 1;
    while ((rc = input_line(&head)) != 0)
        ;
    print_list(head);
    head = exercise(&head);
    printf("\n\n\n");
    print_list(head);
    free_list(head);
    return 0;
}
