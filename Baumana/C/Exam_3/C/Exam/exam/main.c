#include <stdio.h>
#include <stdlib.h>

typedef struct node_t node_t;
struct node_t
{
    int arr;
    node_t *next;
};

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

node_t *find(node_t *head)
{
    node_t *tmp = head;
    int tmp_max = tmp->arr;
    while (tmp)
    {
        if (tmp_max > tmp->arr)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

void print_node(node_t *head)
{
    printf("%d ", head->arr);
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

void print_untill(node_t *head, node_t *node)
{
    node_t *tmp = head;
    while (tmp != node)
    {
        print_node(tmp);
        tmp = tmp->next;
    }
}

node_t *exercise(node_t *head)
{
    node_t *tmp = head;
    node_t *res = find(tmp);
    if (!res)
    {
        printf("0\n");
    }
    else
    {
        print_untill(head, res);
    }
    return head;
}

node_t *create_node(int a)
{
    node_t *tmp = malloc(sizeof(node_t));
    if (!tmp)
        return NULL;
    tmp->arr = a;
    tmp->next = NULL;
    return tmp;
}

node_t *add(node_t *head, node_t *node)
{
    if (!head)
        return node;
    node->next = head;
    head = node;
    return head;
}

int input_line(node_t **head_n)
{
    ssize_t read;
    size_t count = 0;
    char *buf;
    int rc = 0;
    node_t *head = NULL;
    // int  i = 0;
    read = getline(&buf, &count, stdin);
    int a = 0;
    char *start = buf;
    while ((rc = sscanf(buf, "%d", &a)))
    {
        if (a == 0)
        {
            rc = 1;
            break;
        }
        else 
        {
            node_t *tmp = create_node(a);
            if (!tmp)
                break;
            head = add(head, tmp);
        }
        do 
        {
            a /= 10;
            buf++;
        }
        while (a % 10 != 0);
        buf++;
        a = 0;
    }
    if (*buf != '0')
    {
        rc = 3;
    }
    free(start);
    // while ((read = getdelim(&buf, &count, ' ', stdin)) && i < 3)
    // {
    //     int a;
    //     printf("%s\n", buf);
    //     if ((sscanf(buf,"%d", &a)) != 1)
    //     {
    //         free(buf);
    //         break;
    //     }
    //     if (a == 0)
    //     {
    //         rc = 1;
    //         break;
    //     }
    //     else 
    //     {
    //         node_t *tmp = create_node(a);
    //         if (!tmp)
    //             break;
    //         head = add(head, tmp);

    //     }
    //     free(buf);
    //     count = 0;
    //     buf = NULL;
    //     ++i;
    // }
    // int rc;
    // int a;
    // node_t *head = NULL;
    // while ((rc = scanf("%d", &a)) == 1)
    // {
    //     if (a == 0)
    //     {
    //         rc = 1;
    //         break;
    //     }
    //     else
    //     {
    //         node_t *tmp = create_node(a);
    //         if (!tmp)
    //             break;
    //         head = add(head, tmp);
    //         a = 0;
    //     }
    // }
    *head_n = head;
    return rc;
}

int main(void)
{
    node_t *head = NULL;
    int rc = 1;
    rc = input_line(&head);
    if (rc != 1)
    {
        printf("Errror\n");
        return 2;
    }
    if (!head)
    {
        printf("Empty list\n");
        return 1;
    }
    // print_list(head);
    head = exercise(head);
    free_list(head);
    return 0;
}
