#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_



// Структура закрытого типа
struct hash_table_t
{
    item_t **item;  // адрес начала массива элементов 
    size_t size;   // размер таблицы
    size_t count; // количество элементов в хеш таблице
};

// 
typedef struct hash_table_t table_t;


// Структура открытого типа хеширования с коллизиями в виде ДДП
struct hash_table_col_t
{
    itemtree_t **itemtree;  // адрес начала массива элементов (деревья)
    size_t size;   // размер таблицы
    size_t count; // количество неповторяющихся элементов в хеш таблице
    size_t col_amount; // количество коллизий в хеш таблице
};

// Структура хеш-таблицы для обработки данных с коллизией (в виде дерева)
typedef struct hash_table_col_t tablec_t; 



// Структура открытого типа хеширования с коллизиями в виде односвязного линейного списка
struct hash_table_node_t
{
    itemnode_t **itemnode; // адреса начала массива элементов (списков)
    size_t size; // размер таблицы
    size_t count; // количество неповторяющихся элементов в хеш таблице 
    size_t col_amount; // количество коллизий в хеш таблице
};


// Структура хеш-таблицы для обработки данных с коллизией (в виде списков)
typedef struct hash_table_node_t tablen_t;


table_t *hashtable_init(size_t size);
void hashtable_add(table_t *table, item_t *item_n, int hash_func);
void hashtable_remove_word(table_t *table, char *word, int hash_func);
void hashtable_delete(table_t *table);
void hashtable_print(table_t *table);
void hashtable_size(table_t *table);
bool find_word_new(table_t *table, char *name, size_t key, int hash_func, int *amount);
table_t *restruct_new(table_t *table, size_t new_size, int hash_func);
table_t *init_hashtable_from_file_new(char *filename, size_t size_of_hash, int hash_func);



tablec_t *hashtablec_init(size_t size);
void hashtablec_add(tablec_t *table, itemtree_t *item, int hash_func);
void hashtablec_remove_word(tablec_t *table, char *word, int hash_func);
void hashtablec_delete(tablec_t *table);
void hashtablec_pre_delete(tablec_t *table);
void hashtablec_print(tablec_t *table);
void hashtablec_count_elems(tablec_t *table);
bool find_word(tablec_t *table, char *name, size_t key, int hash_func, int *amount);
tablec_t *restruct(tablec_t *table, size_t new_size, int hash_func);
void hashtablec_print_file(FILE *f, tablec_t *table);
tablec_t *init_hashtable_from_file(char *filename, size_t size_of_hash, int hash_func);



tablen_t *hashtablen_init(size_t size);
void hashtablen_add(tablen_t *table, itemnode_t *item, int hash_func);
void hashtablen_remove_word(tablen_t *table, char *word, int hash_func);
void hashtablen_delete(tablen_t *table);
void hashtablen_pre_delete(tablen_t *table);
void hashtablen_print(tablen_t *table);
void hashtablen_count_elems(tablen_t *table);
bool find_nword(tablen_t *table, char *name, size_t key, int hash_func, int *count);
tablen_t *restructn(tablen_t *table, size_t new_size, int hash_func);
void hashtablen_print_file(FILE *f, tablen_t *table);
tablen_t *init_hashtablen_from_file(char *filename, size_t size_of_hash, int hash_func);




char *read_word_from_file(FILE *f);
void change_hashfunc(int *hash_func);


#endif // HASH_TABLE_H_