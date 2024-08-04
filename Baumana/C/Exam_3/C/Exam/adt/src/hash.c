#include "libmy.h"


item_t *create_item(char *buf)
{
    if (!buf)
        return NULL;
    char *tmp = malloc(strlen(buf) + 1);
    if (!tmp)
    {
        free(buf);
        return NULL;
    }
    char end;
    sscanf(buf, "%c", &end);
    if (end == '\n')
        return NULL;
    item_t *item = malloc(sizeof(item_t));
    if (!item)
    {
        free(buf);
        free(tmp);
        return NULL;
    }
    strcpy(tmp, buf);

    item->str = tmp;
    item->key = hash_func(tmp);
    return item;
}

char *hash_func(char *s)
{
    size_t end = strlen(s) - 1;
    char *start = malloc(strlen(s) + 1);
    size_t i = 0;
    for (; i < strlen(s); ++i)
    {
        start[i] = s[end];
        end--;
    }
    start[i] = '\0';
    return start;
}

size_t pos(item_t *item, hash_t *ht)
{
    printf("%s\n", item->key);
    size_t count = atol(item->key);
    printf("%ld\n", count);
    return (count % ht->size); 
}

hash_t *add_hash(hash_t *ht, item_t *item)
{
    size_t hash = pos(item, ht);
    if (ht->arr[hash] == NULL)
    {
        ht->arr[hash] = item;
        ++ht->count;
    }
    else 
    {
        printf("Коллизия\n");
    }  
    return ht;
}

hash_t *create_ht(size_t max)
{
    if (max == 0)
        return NULL;
    hash_t *ht = malloc(sizeof(hash_t));
    ht->size = max;
    ht->count = 0;
    ht->arr = calloc(max, sizeof(item_t *));
    for (size_t i = 0; i < max; ++i)
    {
        ht->arr[i] = NULL;
    } 
    return ht;
}

int create_hash_table(hash_t **head_n)
{
    ssize_t read;
    size_t count = 0;
    char *buf = NULL;
    char *quantity = input_line(1);
    size_t max = atol(quantity);
    free(quantity);
    hash_t *head = create_ht(max);
    if (!head)
        return 1;
    while ((read = getline(&buf, &count, stdin)) != -1)
    {
        item_t *tmp = create_item(buf);
        if (!tmp)
            break;
        head = add_hash(head, tmp);
        free(buf);
        buf = NULL;
        count = 0;
    }
    *head_n = head;
    return 0;
}

void print_item(item_t *item)
{
    printf("Key -> %s Word ->%s\n", item->key, item->str);
}

void print_hash(hash_t *ht)
{
    for (size_t i = 0; i < ht->size; ++i)
    {
        if (ht->arr[i] != NULL)
        {
            printf("%ld\n", i);
            print_item(ht->arr[i]);
        }
    }
}