#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t node_t;

struct node_t
{
    int numbers[2];
    node_t *next;
};

int create_node(char *buf, node_t **tmp)
{
    if (!buf)
        return 2;
    char end;
    int a,b;
    if ((sscanf(buf, "%d %d%c", &a, &b, &end)) != 3)
    {
        free(buf);
        return 2;
    }
    if (end != '\n')
    {
        free(buf);
        return 2;
    }
    node_t *node = malloc(sizeof(node_t));
    if (!node)
    {
        free(buf);
        return 2;
    }
    node->numbers[0] = a;
    node->numbers[1] = b;
    node->next = NULL;
    *tmp = node;
    return 0;
}

node_t *add(node_t *head, node_t *node)
{
    if (head == NULL)
    {
        return node;
    }
    node_t *tmp = head;
    while (tmp->next)
    {
        tmp = tmp->next;
    }
    tmp->next = node;
    return head;
}

void print_node(node_t *head)
{
    printf("%d %d\n", head->numbers[0], head->numbers[1]);
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

void free_list(node_t *head)
{
    while (head)
    {
        node_t *tmp = head;
        head = head->next;
        free(tmp);
    }
}

node_t *find(node_t *head)
{
    node_t *tmp = head;
    while (tmp)
    {
        if (tmp->numbers[0] == tmp->numbers[1])
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

node_t *new_list(node_t **head, node_t *new_head, node_t *find)
{
    if (*head == find)
    {
        if ((*head)->next == NULL)
        {
            find->next = NULL;
            new_head = add(new_head, find);
            *head = NULL;
            return new_head;
        }
        else 
        {
            (*head) = (*head)->next;
            find->next = NULL;
            new_head = add(new_head, find);
            return new_head;
        }
    }
    node_t *tmp = *head;
    while (tmp->next != find)
    {
        tmp = tmp->next;
    }
    if (find->next == NULL)
    {
        tmp->next = NULL;
        new_head = add(new_head, find);
        return new_head;
    }
    else 
    {
        tmp->next = find->next;
        find->next = NULL;
        new_head = add(new_head, find);
        return new_head;
    }    
}

int input_line(node_t **head_n)
{
    ssize_t read;
    size_t count = 0;
    char *buf = NULL;
    node_t *head = NULL;
    int rc = 0;
    while ((read = getline(&buf, &count, stdin)) != -1)
    {
        node_t *tmp = NULL;
        rc = create_node(buf, &tmp);
        if (rc)
        {
            break;
        }
        head = add(head, tmp);
        free(buf);
        buf = NULL;
        count = 0;
    }
    *head_n = head;
    return 0;
}

int main(void)
{   
    int rc = 0;
    node_t *head = NULL;
    while ((rc = input_line(&head)) != 0);
    node_t *tmp = head;
    node_t *new_list_n = NULL;
    while ((tmp = find(head)))
    {
        new_list_n = new_list(&head, new_list_n, tmp);
    }
    print_list(head);
    printf("\n\n");
    print_list(new_list_n);
    free_list(new_list_n);
    free_list(head);
    return 0;
}
