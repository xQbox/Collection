#include <libmy.h>

node_t *create_node(char *buf)
{
    if (!buf)
        return NULL;
    int a, b;
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
        printf("MEM ERROR\n");
        free(buf);
        return NULL;
    }
    tmp->arr[0] = a;
    tmp->arr[1] = b;
    tmp->next = NULL;
    return tmp;
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

node_t *push(node_t *head, node_t *node)
{
    if (!head)
        return node;
    node->next = head;
    return node;
}

node_t *find_node(node_t *head, int (*comp)(node_t *))
{
    node_t *tmp = head;
    while (tmp)
    {
        if (comp(tmp))
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

node_t *remove_node(node_t **head, node_t *find)
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
    while (tmp->next != find)
        tmp = tmp->next;
    if (find == NULL)
    {
        tmp->next = NULL;
        free_node(find);
    }
    else
    {
        tmp->next = find->next;
        free_node(find);
    }
    return *head;
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


int create_list(node_t **head_n)
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


int comp_node(node_t *node)
{
    if (node->arr[0] == node->arr[1])
        return 1;
    return 0;
}
