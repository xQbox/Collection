#include "libmy.h"

node_t *node_push(node_t *head, node_t *node)
{
    node->next = head;
    head = node;
    // printf("%s", head->word);
    return head;
}

bool node_add_to_end(node_t *head, node_t *node)
{
    // if (head->next)
    // {
    node_t *tmp = head;

    while (tmp->next)
    {
        if ((strcmp(tmp->word, node->word)) == 0)
        {
            tmp->count += 1;
            node_clear(node);
            return false;
        } 
        tmp = tmp->next;
    }
    tmp->next = node;
    return true;
    // }
    // else 
    // {
    //     if ((strcmp(head->word, node->word)) == 0)
    //     {
    //         head->count += 1;
    //         node_clear(node);
    //         return false;
    //     } 
    //     head->next = node;
    //     return true;
    // }
}

void node_clear(node_t *node)
{
    if (node)
    {
        free(node->word);
        free(node);
    }
}

node_t *node_find(node_t *head, char *name, int *count)
{
    node_t *tmp = head;
    while(tmp)
    {
        if ((strcmp(name, tmp->word)) == 0)
            return tmp;
        (*count)++;
        tmp = tmp->next;
    }
    return NULL;
}

node_t *node_create(char *word)
{
    node_t *node = calloc(1, sizeof(node_t));
    if (node)
    {
        free(node->word);
        free(node->next);
        // node->word = NULL;
        node->word = word;
        node->count = 1;
        node->next = NULL;
        return node;
    }
    return NULL;
}

void node_iter(node_t *head)
{
    node_t *tmp = head;
    while (tmp)
    {
        printf("%d, %s\n", tmp->count, tmp->word);
        tmp = tmp->next;
    }
}

node_t *node_find_int(node_t *head, char *word)
{
    node_t *tmp = head;
    while(tmp)
    {
        if (strcmp(word, tmp->word) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}


void list_clear(node_t *head)
{
    if (head == NULL)
    {
        return;
    }
    node_t *tmp = head;
    while (tmp)
    {
        tmp = head->next;
        node_clear(head);
        head = tmp;
    }
}


// node_t *remove_node_from_list(node_t *head, char *word)
// {
//     node_t *sr = node_find(head, word);
//     // Если найденный элемент списка последний 
//     if (sr->next == NULL)
//     {
//         if (sr == head)
//         {
//             node_clear(head);
//             head = NULL;
//         }
//         else 
//         {
//             node_clear(sr); // удаляем последний элемент, голова не меняется
//// he
//         }
//     }
//     else if (sr == head)
//     {
//         // Если найденный элемент первый 
//         // Если следующий элемент существует меняем указатель на голову
//         if (head->next)
//         {
//             head = head->next;
//         }
//         // Если следующего элемента нет
//         node_clear(sr);
//         // Голова либо NULL , либо указатель на новую голову
//     }
//     else 
//     {
//         node_t *tmp = head;
//         while (tmp)
//         {
//             if (tmp->next == sr)
//                 break;
//             tmp = tmp->next;
//         }
//         tmp->next = sr->next; // открепляем ячейку списка для удаления
//         node_clear(sr);
// }
//     return head; // Голова либо NULL, либо указатель на новую голову, либо исходная
// }

node_t *remove_node_from_list(node_t *head, char *word)
{
    int count = 0;
    node_t *sr = node_find(head, word, &count);
    // если искомое слово является головой списка
    if (sr == head)
    {
        // Если голова единственный элемент списка
        if (head->next == NULL)
        {
            node_clear(sr);
            head = NULL;
        }
        else 
        {
            // если голова не единственный элемент списка
            // head = NULL;
            head = head->next;
            node_clear(sr);            
        }
    }
    else 
    {
        // если искомое слово не находится в голове
        node_t *tmp = head;
        while (tmp->next != sr) tmp = tmp->next;
        if (sr->next == NULL)
        {
            // искомый элемент последний
            node_clear(sr);
            tmp->next = NULL;
        }
        else 
        {   
            // искомый элемент находится между двух элементов
            tmp->next = sr->next;
            node_clear(sr);
        }
    }
    // Голова либо NULL, либо указатель на новую голову, либо исходная
    return head;
}


void node_print(node_t *head)
{
    if (head)
        printf("[%s_%d]", head->word, head->count);
}

void list_print(node_t *head)
{
    node_t *tmp = head;
    while (tmp) 
    {
        node_print(tmp);
        tmp = tmp->next;
    }
}

void list_print_to_file(FILE *f, node_t *head)
{
    node_t *tmp = head;
    while (tmp) 
    {
        fprintf(f, "%s ", tmp->word);
        tmp = tmp->next;
    }
}



