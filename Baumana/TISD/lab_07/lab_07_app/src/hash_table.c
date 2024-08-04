#include "libmy.h"

//hashtable init 
table_t *hashtable_init(size_t size)
{
    table_t *ptr = (table_t *) malloc(sizeof(table_t));
    if (ptr)
    {
        ptr->count = 0;
        ptr->size = size;
        ptr->item = (item_t **) calloc(ptr->size, sizeof(item_t *));
        if (ptr->item)
        {
            for (size_t i = 0; i < ptr->size; ++i)
            {
                ptr->item[i] = NULL;
            }
            return ptr;
        }
    }
    free(ptr);
    return NULL;
}


// delete hashtable
void hashtable_delete(table_t *table)
{
    if (table)
    {
        for (size_t i = 0; i < table->size; ++i)
        {
            delete_item(table->item[i]);
        }
        free(table->item);
        free(table);
    }
}



// Without collission
void hashtable_add(table_t *table, item_t *item_n, int hash_func)
{
    unsigned long hash;
    if (hash_func == DEFAULTHASH)
    {
        hash = hash_func_one(item_n->key, table->size);
    }
    else if (hash_func == MD5)
    {
        uint8_t result[16];
        md5String(item_n->word, result);
        hash = md_to_string(result, table->size);
    }
    else
    {
        hash = hash_func_three(item_n->key, table->size); 
    }

    if (!(table->item[hash]))
    {
        table->count += 1;
        table->item[hash] = item_n;
    }
    else
    {
        for (size_t i = 0; i < table->size; ++i)
        {
            if (!(table->item[(hash + i) % table->size])) 
            {
                table->item[(hash + i) % table->size] = item_n;
                break;
            }
        }
        // printf("Место уже занято, слово не было добавлено\n");
    }
}


void hashtable_print(table_t *table)
{
    for (size_t i = 0; i < table->size; ++i)
    {
        if (table->item[i] != NULL)
        {
            printf("[%ld]key/word -> {[%ld]--[%s]}\n", i,table->item[i]->key, table->item[i]->word);
        }
        else 
        {
            printf("%ld\n", i);
        }
    }
}



tablec_t *hashtablec_init(size_t size)
{
    tablec_t *ptr = malloc(sizeof(tablec_t));
    if (ptr)
    {
        ptr->itemtree = NULL; // добавлена строчка (без теста)
        ptr->size = size;
        ptr->count = 0;
        ptr->col_amount = 0;
        ptr->itemtree = (itemtree_t **) calloc(size, sizeof(itemtree_t *)); // странное использование 
        if (ptr->itemtree)
        {
            for (size_t i = 0; i < ptr->size; ++i)
            {
                ptr->itemtree[i] = NULL; // скорее всего нужно делать free() из-за calloc (без теста)
            } 
            return ptr;
        }
        free(ptr); // уровень вложенности был изменен (без теста)
    }
    return NULL;
}


void hashtablec_add(tablec_t *table, itemtree_t *item, int hash_func)
{
    unsigned long hash;
    if (hash_func == DEFAULTHASH)
    {
        hash = hash_func_one(item->key, table->size);
    }
    else if (hash_func == MD5)
    {
        uint8_t result[16];
        md5String(item->tree_head->word, result);
        hash = md_to_string(result, table->size);
    }
    else
    {
        hash = hash_func_three(item->key, table->size); 
    }

    // printf("LU -> %lu\n", hash);
    if (!(table->itemtree[hash]))
    {
        table->count += 1;
        // clock_t start = clock();
        table->itemtree[hash] = item;
        // double end = (double) ((clock() - start) / CLOCKS_PER_SEC);
        // printf("Время вставки в пустое дерево: %lf\n", end);
    }
    else
    {
        int rc;
        // clock_t start = clock();
        rc = init_leaf(table->itemtree[hash]->tree_head, item->tree_head);
        // double end =  (double) ((clock() - start) / CLOCKS_PER_SEC);
        // printf("Время вставки в ДДП: %lf\n", end);
        if (rc)
        {
            table->count += 1;
            table->col_amount += 1;
        }
        free(item);
    }
}

void hashtablec_print(tablec_t *table)
{
    printf("Хештаблица: \n\t [%ld] - размер\n\t\t [%ld] - количество записанных элементов\n", table->size, table->count);
    for (size_t i = 0; i < table->size; ++i)
    {
        if (table->itemtree[i] != NULL)
        {
            printf("[%ld]key/word -> \n", i);
            dump(table->itemtree[i]->tree_head);
        }
        // else 
        // {
        //     printf("%ld\n", i);
        // }
    }
}



void hashtablec_print_file(FILE *f, tablec_t *table)
{
    for (size_t i = 0; i < table->size; ++i)
    {
        if (table->itemtree[i] != NULL)
        {
            out(f, table->itemtree[i]->tree_head);
        }
        // else 
        // {
        //     printf("%ld\n", i);
        // }
    }
}

void hashtablec_delete(tablec_t *table)
{
    if (table)
    {
        for (size_t i = 0; i < table->size; ++i)
        {
            delete_itemtree(table->itemtree[i]);
        }
        free(table->itemtree);
        free(table);
    }
}


void hashtablen_print_file_new(FILE *f, table_t *table)
{
    for (size_t i = 0; i < table->size; ++i)
    {
        if (table->item[i] != NULL)
        {
            fprintf(f, "%s ", table->item[i]->word);
        }
    }
}


int find_in_file(char *filename, char *name)
{
    FILE *f;
    f = fopen(filename, "r+");
    int rc = ERR_OK;
    tree_t *tail = leaf_create(); 
    if (rc == ERR_OK)
    {
        while ((rc = read_from_file(f, tail)) == ERR_OK)
        {
            tree_t *leaf = leaf_create_with_name(tail);
            if (strcmp(leaf->word, name) == 0)
            {
                return ERR_OK;
            }
        }
    }
    free(tail->word);
    free(tail);
    fclose(f);
    return ERR_FIND;
}


tablec_t *init_hashtable_from_file(char *filename, size_t size_of_hash, int hash_func)
{
    FILE *f = fopen(filename, "r+");
    char *tmp = NULL;
    tablec_t *hash_table = hashtablec_init(size_of_hash); 
    while ((tmp = read_word_from_file(f)))
    {
        size_t key;
        if (hash_func == DEFAULTHASH)
        {
            key = word_to_key(tmp);
        }
        else if (hash_func == MD5)
        {
            uint8_t result[16];
            md5String(tmp, result);
            key = md_to_string_key(result);
        }
        else
        {
            key = kernigan_to_key(tmp);
        }
        itemtree_t *new = create_itemtree(key, tmp); 
        hashtablec_add(hash_table, new, hash_func);
    }
    fclose(f);
    free(tmp);
    return hash_table;
}


char *read_word_from_file(FILE *f)
{
    char buf[512];
    if ((fscanf(f,"%512s", buf)) != 1)
    {
        return NULL;
    }
    if (buf[strlen(buf) - 1] == '\n')
        buf[strlen(buf) - 1] = '\0';

    if ((buf[strlen(buf) - 1] == ',') || (buf[strlen(buf) - 1] == '.') || (buf[strlen(buf) - 1] == ':'))
        buf[strlen(buf) - 1] = '\0';
    
    if (buf[strlen(buf) - 1] == ';' || buf[strlen(buf) - 1] == '"')
        buf[strlen(buf) - 1] = '\0';

    if (buf[0] == '"')
    {
        for (size_t i = 0; i < strlen(buf); ++i)
        {
            buf[i] = buf[i + 1];
        }
        buf[strlen(buf)] = '\0';
    }
    if (strlen(buf) == 0)
    {
        return NULL;
    }
    char *name = (char *) malloc(sizeof(buf) + 1);
    if (!name)
    {
        return NULL;
    }
    strcpy(name, buf);
    return name;
}


bool find_word(tablec_t *table, char *name, size_t key, int hash_func, int *amount)
{
    unsigned long hash;
    if (hash_func == DEFAULTHASH)
    {
        hash = hash_func_one(key, table->size);
    }
    else if (hash_func == MD5)
    {
        uint8_t result[16];
        md5String(name, result);
        hash = md_to_string(result, table->size);
    }
    else
    {
        hash = hash_func_three(key, table->size);
    }

    if (table->itemtree[hash] != NULL)
    {
        tree_t *rc = find(table->itemtree[hash]->tree_head, name, amount);
        
        if (rc)
        {
            // printf("Дерево\n");
            // dump(table->itemtree[hash]->tree_head);
            // printf("Дерево с корнем в виде искомого слова\n");
            // dump(rc);
            // free(rc);
            return true;
        }
        else 
        {
            // printf("Слово \"%s\" не найдено\n", name);
            return false;
        }
    }
    else 
    {
        // printf("Слово \"%s\" не найдено\n", name);
        return false;
    }
}


void hashtablec_remove_word(tablec_t *table, char *word, int hash_func)
{
    unsigned long hash = 0;
    if (hash_func == DEFAULTHASH)
    {
        size_t key = word_to_key(word);
        hash = hash_func_one(key, table->size);
    }
    else if (hash_func == MD5)
    {
        uint8_t result[16];
        md5String(word, result);
        hash = md_to_string(result, table->size);
    }
    else
    {
        size_t key = kernigan_to_key(word);
        hash = hash_func_three(key, table->size);
    }


    if (table->itemtree[hash] != NULL)
    {
        int amount = 0;
        tree_t *rc = find(table->itemtree[hash]->tree_head, word, &amount);
        
        if (rc)
        {
            // export_tree_to_dot("DEREVO", table->itemtree[hash]->tree_head);
            clock_t start = clock();
            table->itemtree[hash]->tree_head = remove_node(table->itemtree[hash]->tree_head, word);
            double end = (double) ((clock() - start) / CLOCKS_PER_SEC);
            printf("Время удаления: %lf\n", end);
            table->count -= 1;
            table->col_amount -= 1;
            if (hash_is_empty(table->itemtree[hash])) // СОМНИТЕЛЬНО, НО ОКЕЙ .... кажется можно без функции
            { 
                table->itemtree[hash] = NULL;
                table->col_amount += 1;
            }
            // dump(table->itemtree[hash]->tree_head);
            // export_tree_to_dot("DEREVO", table->itemtree[hash]->tree_head);
            printf("Успешно\n");
        }
        else 
        {
            printf("Такого слова нет\n");
        }
    }
    else 
    {
        printf("Такого слова нет\n");
    }
}   

void change_hashfunc(int *hash_func)
{
    printf("Функции доступные к выбору:\n");
    printf("1 - Сумма символов строки деленная на размер хештаблицы\n\t");
    printf("2 - MD5\n\t\t");
    printf("3 - Керниган\n");
    int choose = 10;
    while ((choose > 4) || (choose < 0))
    {
        printf("Введите номер\n");
        char tmp;
        char end[2];
        fscanf(stdin, " %c", &tmp);
        scanf("%*[^\n]");
        fgets(end, sizeof(end), stdin);
        choose = tmp - '0';
        if ((choose > 0) && (choose < 4))
            break;
    }
    if (choose == 1)
    {
        *hash_func = 0;
    }
    else if (choose == 1)
    {
        *hash_func = 1;
    }
    else 
    {
        *hash_func = 2;
    }
}

tablec_t  *restruct(tablec_t  *table, size_t new_size, int hash_func)
{
    FILE *f = fopen("tmp.txt", "w");
    hashtablec_print_file(f, table);
    hashtablec_delete(table);
    fclose(f);
    table = init_hashtable_from_file("tmp.txt", new_size, hash_func);
    system("rm -f tmp.txt");
    return table;
}

table_t *restruct_new(table_t *table, size_t new_size, int hash_func)
{
    FILE *f = fopen("tmp.txt", "w");
    hashtablen_print_file_new(f, table);
    hashtable_delete(table);
    fclose(f);
    table = init_hashtable_from_file_new("tmp.txt", new_size, hash_func);
    system("rm -f tmp.txt");
    return table;
}

/* Перезаписать время так как оно не подсчитывает время которое тратится на вычисления хеша*/
void hashtablen_add(tablen_t *table, itemnode_t *item, int hash_func)
{
    unsigned long hash;
    if (hash_func == DEFAULTHASH)
    {
        hash = hash_func_one(item->key, table->size);
    }
    else if (hash_func == MD5)
    {
        uint8_t result[16];
        md5String(item->node_head->word, result);
        hash = md_to_string(result, table->size);
    }
    else
    {
        hash = hash_func_three(item->key, table->size); 
    }

    // printf("LU -> %lu\n", hash);
    if (!(table->itemnode[hash]))
    {
        table->count += 1;
        // clock_t start = clock();
        table->itemnode[hash] = item;
        // double end = (double) ((clock() - start) / CLOCKS_PER_SEC);
        // printf("Время вставки в пустой список: %lf\n", end);
    }
    else
    {
        int rc;
        // clock_t start = clock();
        rc = node_add_to_end(table->itemnode[hash]->node_head, item->node_head); 
        // double end =  (double) ((clock() - start) / CLOCKS_PER_SEC);
        // printf("Время вставки в ДДП: %lf\n", end);
        if (rc)
        {
            table->count += 1;
            table->col_amount += 1;
        }
        free(item);
    }
}



void hashtablen_remove_word(tablen_t *table, char *word, int hash_func)
{
    unsigned long hash = 0;
    if (hash_func == DEFAULTHASH)
    {
        size_t key = word_to_key(word);
        hash = hash_func_one(key, table->size);
    }
    else if (hash_func == MD5)
    {
        uint8_t result[16];
        md5String(word, result);
        hash = md_to_string(result, table->size);
    }
    else
    {
        size_t key = kernigan_to_key(word);
        hash = hash_func_three(key, table->size);
    }
    if (table->itemnode[hash] != NULL)
    {
        int amount = 0;
        node_t *rc = node_find(table->itemnode[hash]->node_head, word, &amount);
        if (rc)
        {
            table->itemnode[hash]->node_head = remove_node_from_list(table->itemnode[hash]->node_head, word);
            if (table->itemnode[hash]->node_head == NULL)
            {
                table->count -= 1;
                table->itemnode[hash] = NULL;
            }
            else 
            {
                table->count -= 1;
                table->col_amount -= 1;
            }
            printf("Успешно\n");
        }
        else 
        {
            printf("Такого слова нет %s\n", word);
        }
    }
    else 
    {
        printf("Такого слова нет %s\n", word);
    }
}


void hashtablen_delete(tablen_t *table)
{
    if (table)
    {
        for (size_t i = 0; i < table->size; ++i)
        {
            delete_itemnode(table->itemnode[i]);
        }
        free(table->itemnode);
        free(table);
    }
}


void hashtablen_print(tablen_t *table)
{
    printf("Хештаблица: \n\t [%ld] - размер\n\t\t [%ld] - количество записанных элементов\n\t\t\t [%ld] - количество коллизий\n", table->size, table->count, table->col_amount);
    for (size_t i = 0; i < table->size; ++i)
    {
        if (table->itemnode[i] != NULL)
        {
            printf("[%ld] ключ : список \n [ ", i);
            list_print(table->itemnode[i]->node_head);
            printf(" ]\n");
        }
        // else 
        // {
        //     printf("%ld\n", i);
        // }
    }
}



bool find_nword(tablen_t *table, char *name, size_t key, int hash_func, int *count)
{
    unsigned long hash;
    if (hash_func == DEFAULTHASH)
    {
        hash = hash_func_one(key, table->size);
    }
    else if (hash_func == MD5)
    {
        uint8_t result[16];
        md5String(name, result);
        hash = md_to_string(result, table->size);
    }
    else
    {
        hash = hash_func_three(key, table->size);
    }

    if (table->itemnode[hash] != NULL)
    {
        node_t *rc = node_find(table->itemnode[hash]->node_head, name, count);
        
        if (rc)
        {
            // printf("Дерево\n");
            // dump(table->itemtree[hash]->tree_head);
            // printf("Дерево с корнем в виде искомого слова\n");
            // dump(rc);
            // free(rc);
            return true;
        }
        else 
        {
            // printf("Слово \"%s\" не найдено\n", name);
            return false;
        }
    }
    else 
    {
        // printf("Слово \"%s\" не найдено\n", name);
        return false;
    }
}


void hashtablen_print_file(FILE *f, tablen_t *table)
{
    for (size_t i = 0; i < table->size; ++i)
    {
        if (table->itemnode[i] !=  NULL)
        {
            out_n(f, table->itemnode[i]->node_head);
        }
    }
}



tablen_t *restructn(tablen_t *table, size_t new_size, int hash_func)
{
    FILE *f = fopen("tmp1.txt", "w");
    hashtablen_print_file(f, table);
    hashtablen_delete(table);
    fclose(f);
    table = init_hashtablen_from_file("tmp1.txt", new_size, hash_func);
    system("rm -f tmp1.txt");
    return table;
}


tablen_t *hashtablen_init(size_t size)
{
    tablen_t *table = (tablen_t *) malloc(sizeof(tablen_t));
    if (table)
    {
        // table->itemnode = NULL;
        table->itemnode = (itemnode_t **) calloc(size, sizeof(itemnode_t *)); 
        if (table->itemnode)
        {
            table->size = size;
            table->col_amount = 0;
            table->count = 0;
            for (size_t i = 0; i < size; ++i)
            {
                free(table->itemnode[i]);
            }
            return table;
        }
        free(table);
    }
    return NULL;
}


tablen_t *init_hashtablen_from_file(char *filename, size_t size_of_hash, int hash_func)
{
    FILE *f = fopen(filename, "r+");
    tablen_t *table = hashtablen_init(size_of_hash);
    if (table) 
    {
        char *tmp;
        while ((tmp = read_word_from_file(f)))
        {
            size_t key;
            if (hash_func == DEFAULTHASH)
            {
                key = word_to_key(tmp);
            }
            else if (hash_func == MD5)
            {
                uint8_t result[16];
                md5String(tmp, result);
                key = md_to_string_key(result);
            }
            else
            {
                key = kernigan_to_key(tmp);
            }
            itemnode_t *new = create_itemnode(key, tmp); 
            hashtablen_add(table, new, hash_func);
        }
        free(tmp);
        fclose(f);
        return table;
    }
    fclose(f);
    return NULL;
}



table_t *init_hashtable_from_file_new(char *filename, size_t size_of_hash, int hash_func)
{
    FILE *f = fopen(filename, "r+");
    char *tmp = NULL;
    table_t *hash_table = hashtable_init(size_of_hash); 
    while ((tmp = read_word_from_file(f)))
    {
        size_t key;
        if (hash_func == DEFAULTHASH)
        {
            key = word_to_key(tmp);
        }
        else if (hash_func == MD5)
        {
            uint8_t result[16];
            md5String(tmp, result);
            key = md_to_string_key(result);
        }
        else
        {
            key = kernigan_to_key(tmp);
        }
        item_t *new = create_item(key, tmp); 
        hashtable_add(hash_table, new, hash_func);
    }
    fclose(f);
    free(tmp);
    return hash_table;
}


void hashtable_remove_word(table_t *table, char *word, int hash_func)
{
    unsigned long hash = 0;
    if (hash_func == DEFAULTHASH)
    {
        size_t key = word_to_key(word);
        hash = hash_func_one(key, table->size);
    }
    else if (hash_func == MD5)
    {
        uint8_t result[16];
        md5String(word, result);
        hash = md_to_string(result, table->size);
    }
    else
    {
        size_t key = kernigan_to_key(word);
        hash = hash_func_three(key, table->size);
    }
    int amount = 0;
    if (find_word_new(table, word, hash, hash_func, &amount))
    {
        for (size_t i = 0; i < table->size; ++i)
        {
            if ((strcmp(word, table->item[(hash + i) % table->size]->word)) == 0)
            {
                free(table->item[(hash + i) % table->size]->word);
                table->item[(hash + i) % table->size] = NULL;
                break;
            }
        }
    }
    else 
    {
        printf("такого слова нет в таблице\n");
    }

}

bool find_word_new(table_t *table, char *name, size_t key, int hash_func, int *amount)
{
    unsigned long hash;
    if (hash_func == DEFAULTHASH)
    {
        hash = hash_func_one(key, table->size);
    }
    else if (hash_func == MD5)
    {
        uint8_t result[16];
        md5String(name, result);
        hash = md_to_string(result, table->size);
    }
    else
    {
        hash = hash_func_three(key, table->size);
    }

    if (table->item[hash] != NULL)
    {
        for (size_t i = 0; i < table->size; ++i)
        {
            (*amount)++;
            if ((strcmp(name, table->item[(hash + i) % table->size]->word)) == 0)
            {
                return true;
            }
        }
        return false;
    }
    else 
    {
        return false;
    }
}