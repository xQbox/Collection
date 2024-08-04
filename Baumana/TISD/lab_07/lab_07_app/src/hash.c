#include "libmy.h"


// Create node for hashtable
item_t *create_item(size_t key, char *word)
{
    item_t *ptr = (item_t *) malloc(sizeof(item_t));
    if (ptr)
    {
        ptr->key = key;
        ptr->word = NULL;
        ptr->word = word;
        return ptr;    
    }
    return NULL;
}

// Delete node in hashtable
void delete_item(item_t *item)
{
    if (item)
    {
        free(item->word);
        free(item);
    }
}


unsigned long hash_func_one(size_t key, size_t size_of_hashtable)
{
    // printf("LU IN %lu\n", key % TABLE_SIZE);
    return (key % size_of_hashtable);
}


size_t word_to_key(char *word)
{
    size_t k = 0;
    for (size_t i = 0; word[i]; ++i)
    {
        k += word[i];
    }
    return k;
}

unsigned long md_to_string(uint8_t *result, size_t size)
{
    unsigned long final = 0;
    for (size_t i = 0; i < 16; ++i)
    {
        final += (int) result[i];
    }
    return (final % size);
}


/* hash: получает хэш-код для строки s */
size_t kernigan_to_key(char *s)
{
    size_t hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    
    return hashval;
}

unsigned long hash_func_three(size_t key, size_t size)
{
    return key % size;
}

size_t md_to_string_key(uint8_t *result)
{
    size_t final = 0;
    for (size_t i = 0; i < 16; ++i)
    {
        final += (int) result[i];
    }
    return final;
}


itemtree_t *create_itemtree(size_t key, char *word)
{
    itemtree_t *ptr = (itemtree_t *) malloc(sizeof(itemtree_t));
    if (ptr)
    {

        ptr->tree_head = NULL;
        ptr->key = key;
        tree_t *tree_head = leaf_create_with_name_new(word);
        if (tree_head)
        {
            ptr->tree_head = tree_head;
            return ptr;
        }
        tree_clean(tree_head); // сомнительно , но окей
        free(ptr->tree_head);
        free(ptr);
    } 
    free(word);
    return NULL;
}


void delete_itemtree(itemtree_t *item)
{
    if (item)
    {
        tree_clean(item->tree_head);
    }
    free(item);
}


bool hash_is_empty(itemtree_t *item)
{
    if (item->tree_head == NULL)
        return true;
    return false;
}


itemnode_t *create_itemnode(size_t key, char *word)
{
    itemnode_t *ptr = (itemnode_t *) malloc(sizeof(itemnode_t));
    if (ptr)
    {
        ptr->node_head = NULL;
        node_t *head = node_create(word);
        if (head) 
        {
            ptr->key = key;
            ptr->node_head = head;
            return ptr;
        }
        list_clear(ptr->node_head);
        /* TODO возможно стоит добавить удаление ссылки на элемент 
        _хотя она и так равна NULL (без теста) */
        free(ptr);
    }
    free(word);
    return NULL;
}


void delete_itemnode(itemnode_t *item)
{
    if (item)
    {
        list_clear(item->node_head);
        free(item);
    }
}

