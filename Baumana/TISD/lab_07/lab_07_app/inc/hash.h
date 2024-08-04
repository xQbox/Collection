#ifndef HASH_H_
#define HASH_H_

struct hash_item_t 
{
    size_t key;  // ключ хеш таблицы
    // int counter; // количество повторений
    char *word; // слово
};

typedef struct hash_item_t item_t;


item_t *create_item(size_t key, char *word);
void delete_item(item_t *item);


/* Блок работы с деревьями */
// единица данных для хеш функции с коллизией (дерево)
struct hashtree_item_t
{
    size_t key;         // ключ для поиска 
    tree_t *tree_head; //  указатель на голову 
};


typedef struct hashtree_item_t itemtree_t;


itemtree_t *create_itemtree(size_t key, char *word);
void delete_itemtree(itemtree_t *item);



/* Блок работы со списками */
// единица данных для хеш функции с коллизией (список)
struct itemnode_t
{
    size_t key; // ключ для поиска ячейки хеш таблицы
    node_t *node_head; // указатель на голову списка
};


typedef struct itemnode_t itemnode_t;

itemnode_t *create_itemnode(size_t key, char *word);
void delete_itemnode(itemnode_t *item);


// Функция хеширования


size_t word_to_key(char *word);
size_t md_to_string_key(uint8_t *result); 
size_t kernigan_to_key(char *s);
unsigned long hash_func_one(size_t key, size_t size_of_hashtable);
unsigned long md_to_string(uint8_t *result, size_t size);
unsigned long hash_func_three(size_t key, size_t size);

bool hash_is_empty(itemtree_t *item);


#endif // HASH_H_