#ifndef HASH_H_
#define HASH_H_

#define SIZE 100

typedef struct hash_t hash_t;

typedef struct item_t item_t;

struct item_t
{
    char *key;
    char *str;
};

struct hash_t
{
    item_t **arr;
    size_t count;
    size_t size;
};

char *hash_func(char *s);

item_t *create_item(char *buf);

hash_t *add_hash(hash_t *ht, item_t *item);

void item_free(item_t *item);

size_t pos(item_t *item, hash_t *ht);

int create_hash_table(hash_t **head_n);

void print_item(item_t *item);

void print_hash(hash_t *ht);

#endif // HASH_H_