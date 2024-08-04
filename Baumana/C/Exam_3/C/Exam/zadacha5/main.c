#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node_t node_t;

struct node_t
{
    double arr[3];
    node_t *next;
};

node_t *create_node(char *buf)
{
    if (!buf)
        return NULL;
    double a, b, c;
    char end;
    if ((sscanf(buf, "%lf %lf %lf%c", &a, &b, &c, &end)) != 4)
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

node_t *add(node_t *head, node_t *node)
{
    if (!head)
    {
        return node;
    }
    node_t *tmp = head;
    while (tmp->next)
        tmp = tmp->next;
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

node_t *find_min(node_t *head)
{
    node_t *tmp = head;
    node_t *min = head;
    while (tmp)
    {
        if (tmp->arr[2] <= min->arr[2])
        {
            min = tmp;
        }
        tmp = tmp->next;
    }
    return min;
}

double find_rad(node_t *head)
{
    node_t *tmp = head;
    int count = 0;
    double sum = 0;
    while (tmp)
    {
        sum += tmp->arr[2];
        count++;
        tmp = tmp->next; 
    }
    return (sum / count);
}

node_t *new_list(node_t **head, node_t *find, node_t *new_node)
{
    if (*head == find)
    {
        new_node->next = *head;
        *head = new_node;
        return *head;
    }   
    node_t *tmp = *head;
    while (tmp->next != find)
    {
        tmp = tmp->next;
    }
    tmp->next = new_node;
    new_node->next = find;
    return *head;
}

node_t *exercise(node_t **head)
{
    double res = find_rad(*head);
    node_t *find = find_min(*head);
    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node)
        return NULL;
    new_node->arr[0] = find->arr[0];
    new_node->arr[1] = find->arr[1];
    new_node->arr[2] = res;
    new_node->next = NULL;
    *head = new_list(head, find, new_node);
    return *head;
}


void print_node(node_t *head)
{
    printf("%f %f %f\n", head->arr[0], head->arr[1], head->arr[2]);
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
    int rc = 1;
    node_t *head = NULL;
    while ((rc = input_line(&head)) != 0);
    if (!head)
    {
        printf("ERROR\n");
        return 2;
    }
    print_list(head);
    printf("\n\n\n");
    head = exercise(&head);
    print_list(head);
    free_list(head);
    return 0;
}