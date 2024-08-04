#define _GNU_SOURCE
// #include <stdio.h>
// #include <stdlib.h>

// // int main(void)
// // {
// //     printf("Ok\n");
// //     double size = 0;
// //     int rc = 0 ;
// //     if ((fscanf(stdin, "%lf", &size)) != 1)
// //     {
// //         scanf("%*[^\n]");
// //         rc = 1;
// //         printf("ERROR: %d", 1);
// //         return rc;
// //     }
// //     if (size < 1)
// //     {
// //         rc = 2;
// //         printf("ERROR %d", rc);
// //         return rc;
// //     }
// //     size_t count = (int) size;
// //     double *arr = malloc(sizeof(double) * size);
// //     double number = 0;
// //     size_t index = 0;
// //     while (index < count)
// //     {
// //         if ((fscanf(stdin, "%lf", &number)) != 1)
// //         {
// //             rc = 3;
// //             printf("ERROR: %d", rc);
// //             return rc;
// //         }
// //         // printf("%lf\n", number);
// //         arr[index] = number;
// //         // printf("%lf\n", arr[index]);
// //         index++;
// //         number = 0;
// //     }
// //     for (size_t i = 0; i < count; ++i)
// //     {
// //         printf("%lf\n", arr[i]);
// //     }
// //     printf("\n\n");
// //     double min = arr[0];
// //     double *ptr_start = arr;
// //     size_t pos = 0;
// //     for (size_t i = 1; i < count; ++i)
// //     {
// //         if (min > arr[i])
// //         {
// //             pos = i;
// //             min = arr[i];
// //         }
// //     }
// //     double tmp = arr[pos];
// //     arr[pos] = arr[0];
// //     arr[0] = tmp;
// //     for (size_t i = 0; i < count; ++i)
// //     {
// //         printf("%lf\n", arr[i]);
// //     }
// //     free(ptr_start);
// //     return rc;
// // }

// // int main(void)
// // {
// //     char buf[20];
// //     int rc = 0;
// //     if (!(fgets(buf, sizeof(buf), stdin)))
// //     {
// //         rc = 1;
// //         printf("ERROR: %d", rc);
// //         return rc;
// //     }
// //     int size = 0;
// //     if ((sscanf(buf, "%d", &size)) != 1)
// //     {
// //         rc = 1;
// //         printf("ERROR: %d", rc);
// //         return rc;
// //     }
// //     if (size < 1)
// //     {
// //         rc = 2;
// //         printf("ERROR: %d", rc);
// //         return rc;
// //     }
// //     printf("\n%d\n", size);
// // }
// typedef struct node_t node_t;

// struct node_t
// {
//     int array[3];
//     node_t *next;
// };

// node_t *add(node_t *head, node_t *node)
// {
//     if (!head)
//         return NULL;
//     node_t *tmp = head;
//     while (tmp->next)
//     {
//         tmp = tmp->next;
//     }
//     tmp->next = node;
//     return head;
// }

// node_t *create_node(char *buf)
// {
//     if (!buf)
//         return NULL;
//     node_t *tmp = malloc(sizeof(node_t));
//     if (!tmp)
//         return NULL;
//     int a, b, c;
//     // printf("%s\n", buf);
//     if ((sscanf(buf, "%d %d %d", &a, &b, &c)) != 3)
//         return NULL;
//     tmp->array[0] = a;
//     tmp->array[1] = b;
//     tmp->array[2] = c;
//     tmp->next = NULL;
//     return tmp;
// }

// void print_node(node_t *tmp)
// {
//     if (!tmp)
//         return;
//     for (size_t i = 0; i < 3; ++i)
//     {
//         printf("%d ", tmp->array[i]);
//     }
//     printf("\n");
// }

// int main(void)
// {
//     size_t i = 0;
//     ssize_t read;
//     char *buf = NULL;
//     node_t *head = malloc(sizeof(node_t));

//     while ((read = getline(&buf, &i, stdin)) != -1)
//     {
//         node_t *tmp = create_node(buf);
//         if (tmp)
//         {
//             print_node(tmp);
//             head = add(head, tmp);
//         }
//         else
//             break;
//     }
//     node_t *start = head->next;
//     size_t size = 0;
//     while (start)
//     {
//         print_node(start);
//         start = start->next;
//         ++size;
//     }
//     start = head->next;
//     node_t **arr = malloc(sizeof(node_t *) * size);
//     for (size_t i = 0; i < size; ++i)
//     {
//         arr[i] = start;
//         start = start->next;
//     }
//     start = head->next;
//     size_t start_pos = 0;
//     for (size_t i = 0; i < size; ++i)
//     {
//         if (arr[i]->array[1] == arr[i]->array[2])
//         {
//             node_t *tmp = arr[start_pos];
//             arr[start_pos] = arr[i];
//             arr[i] = tmp;
//             start_pos++;
//             i++;
//         }
//     }
//     for (size_t i = 0; i < size; ++i)
//     {
//         print_node(arr[i]);
//     }
// }
// node_t *remove_node_from_list(node_t *head, char *word)
// {
//     int count = 0;
//     node_t *sr = node_find(head, word, &count);
//     // если искомое слово является головой списка
//     if (sr == head)
//     {
//         // Если голова единственный элемент списка
//         if (head->next == NULL)
//         {
//             node_clear(sr);
//             head = NULL;
//         }
//         else
//         {
//             // если голова не единственный элемент списка
//             // head = NULL;
//             head = head->next;
//             node_clear(sr);
//         }
//     }
//     else
//     {
//         // если искомое слово не находится в голове
//         node_t *tmp = head;
//         while (tmp->next != sr) tmp = tmp->next;
//         if (sr->next == NULL)
//         {
//             // искомый элемент последний
//             node_clear(sr);
//             tmp->next = NULL;
//         }
//         else
//         {
//             // искомый элемент находится между двух элементов
//             tmp->next = sr->next;
//             node_clear(sr);
//         }
//     }
//     // Голова либо NULL, либо указатель на новую голову, либо исходная
//     return head;
// }
// Exam exercise for

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node_t node_t;

struct node_t
{
    int arr[3];
    node_t *next;
};

void free_node(node_t *tmp)
{
    free(tmp);
}

void free_list(node_t *head)
{
    if (!head)
        return;
    while (head)
    {
        node_t *tmp = head;
        head = head->next;
        free_node(tmp);
    }
}

node_t *create_node(char *buf, int *flag)
{
    node_t *node = malloc(sizeof(node_t));
    if (!node)
        return NULL;
    if (!buf)
    {
        free_node(node);
        return NULL;
    }
    int a, b, c;
    char str_off;
    if ((sscanf(buf, "%d %d %d%c", &a, &b, &c, &str_off)) != 4)
    {
        free_node(node);
        free(buf);
        return NULL;
    }
    if (str_off != '\n')
    {
        *flag = 1;
        free_node(node);
        free(buf);
        return NULL;
    }
    node->arr[0] = a;
    node->arr[1] = b;
    node->arr[2] = c;
    node->next = NULL;
    return node;
}

node_t *add(node_t *head, node_t *node)
{
    if (!head)
    {
        node->next = head;
        head = node;
        return head;
    }
    node_t *tmp = head;
    while (tmp->next)
    {
        tmp = tmp->next;
    }
    tmp->next = node;
    return head;
}

node_t *remove_node(node_t *head, node_t *node)
{
    if (!node)
        return head;
    if (!head)
        return NULL;
    if (head == node)
    {
        free_node(head);
        return NULL;
    }
    if (head->next == node)
    {
        free_node(head->next);
        head->next = NULL;
    }
    node_t *tmp = head, *prev = head;
    tmp = tmp->next;
    int flag = 0;
    while (tmp)
    {
        prev->next = tmp;
        if (tmp == node)
        {
            prev->next = NULL;
            flag = 1;
        }
        if (flag)
        {
            node_t *a = tmp;
            tmp = tmp->next;
            free_node(a);
            flag = 0;
        }
        else
        {
            tmp = tmp->next;
            prev = prev->next;
        }
    }
    return head;
}

void print_node(node_t *tmp)
{
    if (!tmp)
        return;
    for (size_t i = 0; i < 3; ++i)
    {
        printf("%d ", tmp->arr[i]);
    }
    printf("\n");
}

void print_list(node_t *head)
{
    if (!head)
        return;
    node_t *tmp = head;
    while (tmp)
    {
        print_node(tmp);
        tmp = tmp->next;
    }
}

// int main(void)
// {
//     ssize_t read;
//     char *buf = NULL;
//     size_t count = 0;
//     node_t *head = NULL;
//     int rc = 0;
//     while ((read = getline(&buf, &count, stdin)) != -1)
//     {
//         node_t *tmp = create_node(buf, &rc);
//         if (!tmp)
//         {
//             break;
//         }
//         free(buf);
//         buf = NULL;
//         head = add(head, tmp);
//     }
//     if (rc != 0)
//     {
//         free_list(head);
//         return rc;
//     }
//     print_list(head);
//     node_t *tmp = head;
//     while (tmp)
//     {
//         if (tmp->arr[1] <= 0 || tmp->arr[2] <= 0)
//         {
//             head = remove_node(head, tmp);
//             if (!head)
//                 break;
//             tmp = head;
//         }
//         tmp = tmp->next;
//     }
//     if (!head)
//         return 2;
//     printf("\n\n\n");
//     print_list(head);
//     free_list(head);
//     return 0;
// }

node_t *find(node_t *head)
{
    node_t *tmp = head;
    while (tmp)
    {
        if (tmp->arr[1] == tmp->arr[2])
        {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

node_t *find1(node_t *head)
{
    node_t *tmp = head;
    while (tmp)
    {
        if (tmp->arr[1] != tmp->arr[2])
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

void change_node_place(node_t **head, node_t *find, node_t **new_head)
{
    if (!head || !find)
        return;
    if (*head == find)
    {
        node_t *node = *head;
        *head = (*head)->next;
        node->next = NULL;
        *new_head = add(*new_head, node);
        return;
    }
    node_t *tmp = *head;
    while (tmp->next != find)
    {
        tmp = tmp->next;
    }
    if (find->next == NULL)
    {
        tmp->next = NULL;
        *new_head = add(*new_head, find);
    }
    else
    {
        tmp->next = find->next;
        find->next = NULL;
        *new_head = add(*new_head, find);
    }
}

node_t *make_nedded_list(node_t **head, node_t *new_head, node_t *(*find)(node_t *head))
{
    if (!head)
        return NULL;
    node_t *tmp = *head;
    node_t *find_n = NULL;
    while ((find_n = find(tmp)))
    {
        change_node_place(&tmp, find_n, &new_head);
    }
    *head = tmp;
    // print_list(new_head);
    // print_list(*head);
    return new_head;
}

int main(void)
{
    ssize_t read;
    char *buf = NULL;
    size_t count = 0;
    node_t *head = NULL;
    int flag = 0;
    while ((read = getline(&buf, &count, stdin)) != -1)
    {
        node_t *tmp = create_node(buf, &flag);
        if (!tmp)
            break;
        head = add(head, tmp);
        free(buf);
        buf = NULL;
    }
    if (flag != 0)
    {
        free_list(head);
        printf("Error\n");
        return 1;
    }
    node_t *double_end_head = make_nedded_list(&head, NULL, find);
    print_list(double_end_head);
    printf("\n\n\n");
    double_end_head = add(double_end_head, head);
    print_list(double_end_head);
    // printf("%p", (void *) new_head);
    free_list(double_end_head);
    return 0;
}
