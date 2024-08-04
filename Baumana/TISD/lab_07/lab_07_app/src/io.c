#include "libmy.h"

int choose(int choice, tree_t **tree_head, char *filename, tablec_t **table, size_t *size_of_hashtable, int *func_hash, tablen_t **table_n, size_t *size_of_hashtable_sec, int *hash_func_sec, table_t **table_new, size_t *size_of, int *hash_func_new)
{
    if (choice == EXIT)
    {
        *tree_head = from_bst_afl(*tree_head);
        printf("Успешно\n");
    }
    if (choice == PRINTTREE)
    {
        export_tree_to_dot("DEREVO", *tree_head);
        dump(*tree_head);
    }
    else if (choice == ADDWORDINTREE)
    {
        printf("Введите слово для добавления в дерево\n>>");
        char name[256];
        
        fgets(name, sizeof(name), stdin);
        // printf("%s\n", name); 
        if (name[strlen(name) - 1] == '\n')
        {
            name[strlen(name) - 1] = '\0';
        }
        tree_t tmp = {1, name, NULL, NULL};
        tree_t *leaf = leaf_create_with_name(&tmp);
        init_leaf(*tree_head, leaf);
    }   
    else if (choice == ADDWORDINFILE)
    {
        char name[256];
        printf("Введите слово для вставки в файл`\n>>");
        fscanf(stdin, "%256s", name);
        scanf("%*[^\n]");
        size_t tmp_size = strlen(name);
        char new_name[tmp_size];
        strcpy(new_name, name);
        printf("Введите место для вставки слова\n");
            long new_size = 0;
            int pos;
            FILE *f = fopen("text.txt", "rb+");
            char symbol;
            int A[ARR_SIZE];
            size_t index;
            while ((symbol = getc(f)) != EOF)
            {
                if (symbol == ' ')
                {
                    A[index] = ftell(f);
                    index++;
                }
                new_size ++;
            }
            fseek(f, 0, SEEK_SET);

            printf("Размер файла в байтах %ld\n", new_size);
            printf("Введите позицию для записи в файл\n");
            if ((fscanf(stdin, "%d", &pos)) != 1)
            {
                printf("Ошибка ввода\n");
                return ERR_NUM;
            }
            if ((pos > new_size) || (pos < 0))
            {
                printf("Ошибка позиции\n");
                return ERR_NUM;
            }
            scanf("%*[^\n]");
            int flag  = 0;
            int free_pos = binar_search(A, index, pos, &flag);
            pos = A[free_pos];
            char M[new_size - pos + 1];
            fseek(f, pos, SEEK_SET);
            fread(M, sizeof(char), new_size - pos, f);
            M[new_size - pos] = '\0';
            fseek(f, pos, SEEK_SET);
            fwrite(new_name, sizeof(new_name) , 1, f);
            char space = ' ';
            fwrite(&space, sizeof(space), 1, f);
            fwrite(M, sizeof(M) - 1, 1, f);
            fclose(f);
            char tmp[2];
            fgets(tmp, sizeof(char), stdin);
    }
    else if (choice == OPENNEWFILE)
    {
        printf("Введите название нового файла для открытия и инициализации\n>>");
        char tmp[256];
        fgets(tmp, sizeof(tmp), stdin);
        if (tmp[strlen(tmp) - 1] == '\n')
        {
            tmp[strlen(tmp) - 1] = '\0';
        }
        char file[strlen(tmp) + 1];
        strcpy(file, tmp);
        printf("%s\n", file);
        printf("%d\n", file_check(file));
        if (!file_check(file))
        {
            tree_clean(*tree_head);
            *tree_head = NULL;
            read_file(file, tree_head);
            printf("%s %d\n", (*tree_head)->word, (*tree_head)->counter);
            hashtablec_delete(*table);
            hashtablen_delete(*table_n);
            hashtable_delete(*table_new);
            *table = init_hashtable_from_file(file, *size_of_hashtable, *func_hash);
            *table_n = init_hashtablen_from_file(file, *size_of_hashtable_sec, *func_hash);
            *table_new = init_hashtable_from_file_new(file, *size_of, *func_hash);
            filename = file;
        }
        else 
        {
            printf("Ошибка при работе с файлом \n");
        }
    }
    else if (choice == FIND)
    {
        char name[256];
        printf("Введите слово для поиска в файле\n>>");
        fscanf(stdin, "%256s", name);
        scanf("%*[^\n]");
        size_t tmp_size = strlen(name);
        char new_name[tmp_size];
        strcpy(new_name, name);
        tree_t *find_result = NULL;
        clock_t a = clock();
        // printf("%p\n" (void *) *tree_head);
        int amount = 0;
        find_result = find(*tree_head, name, &amount);
        // printf("%p\n" (void *) *tree_head);
        double fin_time = (double) (clock() - a) / CLOCKS_PER_SEC; 
        if (find_result)
        {
            clock_t b = clock();
            find_in_file(filename, new_name);
            double time_end = (double) (clock() - b) / CLOCKS_PER_SEC; 
            printf("Поиск :\nв дереве %lf\nв файле %lf\n", fin_time, time_end);
            printf("Количество сравнений в дереве %d ", amount);
        }
        else 
        {
            printf("Такого слова нет: %s\n", new_name);
        }
    }
    else if (choice == DELETEINTREE)
    {
        char name[256];
        printf("Введите слово для удаления\n");
        fscanf(stdin, "%256s", name);
        size_t tmp_size = strlen(name);
        char new_name[tmp_size];
        strcpy(new_name, name);
        int amount = 0;
        tree_t *result = find(*tree_head, new_name, &amount);
        if (result)
        {
            clock_t a = clock();
            *tree_head = remove_node(*tree_head, new_name);
            double end = (double) (clock() - a) / CLOCKS_PER_SEC;
            printf("Время на удаление : %lf\n", end);
        }
        else 
        {
            printf("слова нет в дереве\n");
        }
    }
    else if (choice == DELETEINFILE)
    {
        FILE *f = fopen(filename, "r"); 
        char name[256];
        int rc ;
        printf("Введите слово для удаления\n");
        fscanf(stdin, "%256s", name);
        size_t tmp_size = strlen(name);
        char new_name[tmp_size];
        strcpy(new_name, name);
        rc = find_in_file(filename, new_name);
        char name_new[256];
        long pos_after_word, pos_before_word;
        if (!rc)
        {
            while ((fscanf(f, "%256s", name_new)) == 1)
            {
                if (strcmp(new_name, name_new) == 0)
                {
                    pos_after_word = ftell(f);
                    // printf("pos -> %ld", pos_after_word);
                    pos_before_word = pos_after_word - strlen(name_new) ;
                    // printf("pos -> %ld", pos_before_word);
                    break;
                }   
            }
            char FILE_END[20000];
            int index = 0;
            char k;
            while ((k = getc(f)) != EOF)
            {
                FILE_END[index] = k;
                index++;
            }
            fseek(f, 0, SEEK_SET);
            char FILE_START[20000];
            int i = 0;
            clock_t a = clock();
            while (i < pos_before_word)
            {
                FILE_START[i] = getc(f);
                i++;
            }
            fclose(f);
            f = fopen(filename, "w");
            int p = 0;
            while (p < i)
            {
                fprintf(f, "%c", FILE_START[p]);
                p++;
            }
            p = 0;
            while (p < index)
            {
                fprintf(f, "%c", FILE_END[p]);
                p++;
            }
            double end = (double) (clock() - a) / CLOCKS_PER_SEC;
            printf("Время на удаление : %lf\n", end);
            fclose(f);
        }
        else 
        {
            printf("слова нет в файле\n");
        }
    }
    else if (choice ==  WORK_WITH_HASHTABLE)
    {
        int choose_hash = 0;
        char tmp;
        char free_space[2];
        while (choose_hash != EXITHASH)
        {
            double res = (double) ((*table)->col_amount) / ((*table)->count) * 100;
        
            if (res > 20.)
            {
                printf("\t\tВнимание!\n\t\tВ таблице высокий процент коллизий!\n\t\t"
                "Рекомендуется сменить хеш-функцию или реструктуризировать таблицу\n");
            }
            hashmenu_print();
            choose_hash = 0;
            if ((fscanf(stdin, " %c", &tmp)) == 1)
            {
                scanf("%*[^\n]");
                
                fgets(free_space, sizeof(free_space), stdin);
                if (tmp > '0' && tmp < '9')
                {
                    sscanf(&tmp, "%d", &choose_hash);
                    choose_hash--;
                    choose_hash_func(choose_hash, table, size_of_hashtable, func_hash, filename);
                }
                else 
                {
                    continue;
                }
            }
        }
    }
    else if (choice ==  WORK_WITH_HASHTABLE_LIST)
    {
        int choose_hash = 0;
        char tmp;
        char free_space[2];
        while (choose_hash != EXITHASH)
        {
            double res = (double) ((*table_n)->col_amount) / ((*table_n)->count) * 100;
            
            if ( res > 20.)
            {
                printf("\t\tВнимание!\n\t\tВ таблице высокий процент коллизий!\n\t\t"
                "Рекомендуется сменить хеш-функцию или реструктуризировать таблицу\n");
            }
            hashlistmenu_print();
            choose_hash = 0;
            if ((fscanf(stdin, " %c", &tmp)) == 1)
            {
                scanf("%*[^\n]");
                
                fgets(free_space, sizeof(free_space), stdin);
                if (tmp > '0' && tmp < '9')
                {
                    sscanf(&tmp, "%d", &choose_hash);
                    choose_hash--;
                    choose_hash_list(choose_hash, table_n, size_of_hashtable_sec, hash_func_sec, filename);
                }
                else 
                {
                    continue;
                }
            }
        }
    }
    else if (choice ==  WORK_WITH)
    {
        int choose_hash = 0;
        char tmp;
        char free_space[2];
        while (choose_hash != EXITHASH)
        {
            hashlistmenu_print();
            choose_hash = 0;
            if ((fscanf(stdin, " %c", &tmp)) == 1)
            {
                scanf("%*[^\n]");
                
                fgets(free_space, sizeof(free_space), stdin);
                if (tmp > '0' && tmp < '9')
                {
                    sscanf(&tmp, "%d", &choose_hash);
                    choose_hash--;
                    choose_hash_func_two(choose_hash, table_new, size_of, hash_func_new, filename);
                }
                else 
                {
                    continue;
                }
            }
        }
    }
    return ERR_OK;
}

void print(tree_t *head)
{
    fprintf(stdout, "\"%s\" встречено %d - раз\n", head->word, head->counter);
}



void out(FILE *f, tree_t *head)
{
    if (head)
    {
        // pre order
        out(f, head->left);
     
        fprintf(f,"%s ", head->word); // in order 
        out(f, head->right);
        // post order
    }
}


void menu_print()
{
    // system("clear");
    printf("\nОсновное меню программы\n\t");
    printf("0 - Из ДДП в АВЛ\n\t");
    printf("1 - Вывод дерева\n\t");
    printf("2 - Добавление слова в дерево\n\t");
    printf("3 - Добавление слова в файл\n\t");
    printf("4 - Открыть другой файл\n\t");
    printf("5 - Поиск\n\t");
    printf("6 - Удаление в дереве\n\t");
    printf("7 - Удаление в файле\n\t");
    printf("8 - Работа с хеш-таблицей( деревья )\n\t");
    printf("9 - Работа с хеш-таблицей( список )\n\t");
    printf("h - Закрытое хеширование\n\t");
    printf("e - Завершение работы программы\n");
    
}

void hashmenu_print()
{
    printf("\nХеш меню \n\t");
    printf("1 - Вывод\n\t");  
    printf("2 - Добавление в хеш-таблицу\n\t");
    printf("3 - Удаление из хеш-таблицы\n\t");
    printf("4 - Изменение хеш-функция\n\t");
    printf("5 - Реструктуризация хеш-функции\n\t");
    printf("6 - Поиск в хеш-функции\n\t");
    printf("7 - Количество неповторяющихся элементов\n\t");
    printf("8 - Завершение работы программы\n");
}

void hashlistmenu_print()
{
    printf("\nХеш меню \n\t");
    printf("1 - Вывод\n\t");  
    printf("2 - Добавление в хеш-таблицу\n\t");
    printf("3 - Удаление из хеш-таблицы\n\t");
    printf("4 - Изменение хеш-функция\n\t");
    printf("5 - Реструктуризация хеш-функции\n\t");
    printf("6 - Поиск в хеш-функции\n\t");
    printf("7 - Количество неповторяющихся элементов\n\t");
    printf("8 - Завершение работы программы\n");
}

int choose_hash_func(int choose, tablec_t **table, size_t *size_of_hashtable, int *func_hash, char *filename)
{
    if (choose == INITHASHTABLE)
    {
        hashtablec_print(*table);
    }
    else if (choose == ADDTOHASH)
    {

        char name[256];
        printf("Введите слово для добавления\n");
        fscanf(stdin, "%256s", name);
        char *new_name = malloc(strlen(name) + 1);
        strcpy(new_name, name);
        size_t key;
        if (*func_hash == DEFAULTHASH)
        {
            key = word_to_key(new_name);
        }
        else if (*func_hash == MD5)
        {
            uint8_t result[16];
            md5String(new_name, result);
            key = md_to_string_key(result);
        }
        else
        {   
            key = kernigan_to_key(new_name);
        }

        itemtree_t *item = create_itemtree(key, new_name);
        hashtablec_add(*table, item, *func_hash);
    }
    else if (choose == DELETEFROMHASH)
    {
        char name[256];
        int hash_func_true = *func_hash;
        printf("Введите слово для удаления\n");
        fscanf(stdin, "%256s", name);
        if (name[strlen(name) - 1] == '\n')
            name[strlen(name) - 1] = '\0';    
        char new_name[strlen(name) + 1];
        strcpy(new_name, name);
        if (hash_func_true != *func_hash)
            *func_hash = hash_func_true; 
        hashtablec_remove_word(*table, new_name, *func_hash);   
    }
    else if (choose == CHANGEHASHFUNCION)
    {
        change_hashfunc(func_hash);
    }
    else if (choose == RESTRUCTHASH)
    {
        size_t new_size; 
        printf("Введите новый размер хештаблицы\n>>");
        if ((fscanf(stdin, "%lu",  &new_size)) == 1)
        {
            if ((*table = restruct(*table, new_size, *func_hash))) // убрал проверку на невозможность увеличить память
            {
                *size_of_hashtable = new_size;
            }
            if (*table)
            {  
               printf("Успешно\n");
            }
        }
        else 
        {
            printf("Не удалось изменить размер\n");
        }
        scanf("%*[^\n]");   
    }
    else if (choose == FINDINHASH)
    {
        char name[256];
        int hash_func_true = *func_hash;
        printf("Введите слово для поиска\n");
        fscanf(stdin, "%256s", name);
        char new_name[strlen(name)+1];
        strcpy(new_name, name);
        size_t key;
        if (*func_hash == DEFAULTHASH)
        {
            key = word_to_key(new_name);
        }
        else if (*func_hash == MD5)
        {
            uint8_t result[16];
            md5String(new_name, result);
            key = md_to_string_key(result);
        }
        else
        {
            key = kernigan_to_key(new_name);
        }
        if (hash_func_true != *func_hash)
            *func_hash = hash_func_true;
        int rc;
        int amount = 0;
        clock_t start = clock();
        rc = find_word(*table, new_name, key, *func_hash, &amount);
        double end = (double) (clock() - start) / CLOCKS_PER_SEC;
        if (rc)
        {
            printf("Успешно\n");
        } 
        printf("Время поиска в хеш-таблице: %lf\n", end);
    }
    else if (choose == ELEMS)
    {
        FILE *f = fopen(filename, "r+");
        int counter = 0;
        char *tmp = NULL;
        double res = 0;
        double amount_all = 0;
        while ((tmp = read_word_from_file(f)))
        {
            int hash_func_true = *func_hash;
                size_t key;
            if (*func_hash == DEFAULTHASH)
            {
                key = word_to_key(tmp);
            }
            else if (*func_hash == MD5)
            {
                uint8_t result[16];
                md5String(tmp, result);
                key = md_to_string_key(result);
            }
            else
            {
                key = kernigan_to_key(tmp);
            }
            if (hash_func_true != *func_hash)
                *func_hash = hash_func_true;
            int amount = 0;
            clock_t start = clock();
            find_word(*table, tmp, key, *func_hash, &amount);
            res += (double) (clock() - start) / CLOCKS_PER_SEC;
            free(tmp);
            amount_all += amount;
            tmp = NULL;
            counter++;
        }
        res = res / counter;
        amount_all = amount_all / counter;
        printf("Количество неповторяющихся элементов %ld\nКоличество коллизий %ld\n" , (*table)->count, (*table)->col_amount);
        printf("Размер по памяти %ld\n", sizeof(tree_t) * (*table)->count);
        printf("Усредненное время поиска всех слов из файла %lf \n", res);
        printf("Усредненное количество сравнений для поиска слова %.3lf \n", amount_all);
    }

    return ERR_OK;
}



int choose_hash_list(int choose, tablen_t **table_n, size_t *size_of_hashtable_sec, int *hash_func_sec, char *filename)
{
    if (choose == INITHASHTABLE)
    {
        hashtablen_print(*table_n);
    }
    else if (choose == ADDTOHASH)
    {

        char name[256];
        printf("Введите слово для добавления\n");
        fscanf(stdin, "%256s", name);
        char *new_name = malloc(strlen(name) + 1);
        strcpy(new_name, name);
        size_t key;
        if (*hash_func_sec == DEFAULTHASH)
        {
            key = word_to_key(new_name);
        }
        else if (*hash_func_sec == MD5)
        {
            uint8_t result[16];
            md5String(new_name, result);
            key = md_to_string_key(result);
        }
        else
        {   
            key = kernigan_to_key(new_name);
        }

        itemnode_t *item = create_itemnode(key, new_name);
        hashtablen_add(*table_n, item, *hash_func_sec);
    }
    else if (choose == DELETEFROMHASH)
    {
        char name[256];
        int hash_func_true = *hash_func_sec;
        printf("Введите слово для удаления\n");
        fscanf(stdin, "%256s", name);
        if (name[strlen(name) - 1] == '\n')
            name[strlen(name) - 1] = '\0';    
        char new_name[strlen(name) + 1];
        strcpy(new_name, name);
        if (hash_func_true != *hash_func_sec)
            *hash_func_sec = hash_func_true; 
        hashtablen_remove_word(*table_n, new_name, *hash_func_sec);   
    }
    else if (choose == CHANGEHASHFUNCION)
    {
        change_hashfunc(hash_func_sec);
    }
    else if (choose == RESTRUCTHASH)
    {
        size_t new_size; 
        printf("Введите новый размер хештаблицы\n>>");
        if ((fscanf(stdin, "%lu",  &new_size)) == 1)
        {
            if ((*table_n = restructn(*table_n, new_size, *hash_func_sec))) // убрал проверку на невозможность увеличить память
            {
                *size_of_hashtable_sec = new_size;
            }
            if (*table_n)
            {  
               printf("Успешно\n");
            }
        }
        else 
        {
            printf("Не удалось изменить размер\n");
        }
        scanf("%*[^\n]");   
    }
    else if (choose == FINDINHASH)
    {
        char name[256];
        int hash_func_true = *hash_func_sec;
        printf("Введите слово для поиска\n");
        fscanf(stdin, "%256s", name);
        char new_name[strlen(name)+1];
        strcpy(new_name, name);
        size_t key;
        if (*hash_func_sec == DEFAULTHASH)
        {
            key = word_to_key(new_name);
        }
        else if (*hash_func_sec == MD5)
        {
            uint8_t result[16];
            md5String(new_name, result);
            key = md_to_string_key(result);
        }
        else
        {
            key = kernigan_to_key(new_name);
        }
        if (hash_func_true != *hash_func_sec)
            *hash_func_sec = hash_func_true;
        int rc;
        int amount = 0;
        clock_t start = clock();
        rc = find_nword(*table_n, new_name, key, *hash_func_sec, &amount);
        double end = (double) (clock() - start) / CLOCKS_PER_SEC;
        if (rc)
        {
            printf("Успешно\n");
        } 
        printf("Время поиска в хеш-таблице: %lf\n", end);
    }
    else if (choose == ELEMS)
    {
        FILE *f = fopen(filename, "r+");
        int counter = 0;
        char *tmp = NULL;
        double res = 0;
        double amount_all = 0;
        while ((tmp = read_word_from_file(f)))
        {
            int hash_func_true = *hash_func_sec;
                size_t key;
            if (*hash_func_sec == DEFAULTHASH)
            {
                key = word_to_key(tmp);
            }
            else if (*hash_func_sec == MD5)
            {
                uint8_t result[16];
                md5String(tmp, result);
                key = md_to_string_key(result);
            }
            else
            {
                key = kernigan_to_key(tmp);
            }
            if (hash_func_true != *hash_func_sec)
                *hash_func_sec = hash_func_true;
            int amount = 0;
            clock_t start = clock();
            find_nword(*table_n, tmp, key, *hash_func_sec, &amount);
            res += (double) (clock() - start) / CLOCKS_PER_SEC;
            free(tmp);
            amount_all += amount;
            tmp = NULL;
            counter++;
        }
        res = res / counter;
        amount_all = amount_all / counter;
        printf("Количество неповторяющихся элементов %ld\nКоличество коллизий %ld\n" , (*table_n)->count, (*table_n)->col_amount);
        printf("Размер по памяти %ld\n", sizeof(node_t) * (*table_n)->count);
        printf("Усредненное время поиска всех слов из файла %lf \n", res);
        printf("Усредненное количество сравнений для поиска слова %.3lf \n", amount_all);
    }


    return ERR_OK;
}


int choose_hash_func_two(int choose, table_t **table, size_t *size_of_hashtable, int *func_hash, char *filename)
{
    if (choose == INITHASHTABLE)
    {
        hashtable_print(*table);
    }
    else if (choose == ADDTOHASH)
    {
        char name[256];
        printf("Введите слово для добавления\n");
        fscanf(stdin, "%256s", name);
        char *new_name = malloc(strlen(name) + 1);
        strcpy(new_name, name);
        size_t key;
        if (*func_hash == DEFAULTHASH)
        {
            key = word_to_key(new_name);
        }
        else if (*func_hash == MD5)
        {
            uint8_t result[16];
            md5String(new_name, result);
            key = md_to_string_key(result);
        }
        else
        {   
            key = kernigan_to_key(new_name);
        }
        if ((*table)->size > (*table)->count)
        {
            item_t *item = create_item(key, new_name);
            hashtable_add(*table, item, *func_hash);
        }
        else 
        {
            printf("Не могу инициализировать таблицу\n");
        }
    }
    else if (choose == DELETEFROMHASH)
    {
        char name[256];
        int hash_func_true = *func_hash;
        printf("Введите слово для удаления\n");
        fscanf(stdin, "%256s", name);
        if (name[strlen(name) - 1] == '\n')
            name[strlen(name) - 1] = '\0';    
        char new_name[strlen(name) + 1];
        strcpy(new_name, name);
        if (hash_func_true != *func_hash)
            *func_hash = hash_func_true; 
        hashtable_remove_word(*table, new_name, *func_hash);   
    }
    else if (choose == CHANGEHASHFUNCION)
    {
        change_hashfunc(func_hash);
    }
    else if (choose == RESTRUCTHASH)
    {
        size_t new_size; 
        printf("Введите новый размер хештаблицы\n>>");
        if ((fscanf(stdin, "%lu",  &new_size)) == 1)
        {
            if (new_size > (*table)->count)
            { 
                if ((*table = restruct_new(*table, new_size, *func_hash))) // убрал проверку на невозможность увеличить память
                {
                    *size_of_hashtable = new_size;
                }
                if (*table)
                {  
                printf("Успешно\n");
                }
            }
            else 
            {
                printf("Не могу инициализровать таблицу\n");
            }
        }
        else 
        {
            printf("Не удалось изменить размер\n");
        }
        scanf("%*[^\n]");   
    }
    else if (choose == FINDINHASH)
    {
        char name[256];
        int hash_func_true = *func_hash;
        printf("Введите слово для поиска\n");
        fscanf(stdin, "%256s", name);
        char new_name[strlen(name)+1];
        strcpy(new_name, name);
        size_t key;
        if (*func_hash == DEFAULTHASH)
        {
            key = word_to_key(new_name);
        }
        else if (*func_hash == MD5)
        {
            uint8_t result[16];
            md5String(new_name, result);
            key = md_to_string_key(result);
        }
        else
        {
            key = kernigan_to_key(new_name);
        }
        if (hash_func_true != *func_hash)
            *func_hash = hash_func_true;
        int rc, amount = 0;
        clock_t start = clock();
        rc = find_word_new(*table, new_name, key, *func_hash, &amount);
        double end = (double) (clock() - start) / CLOCKS_PER_SEC;
        if (rc)
        {
            printf("Успешно\n");
        } 
        printf("Время поиска в хеш-таблице: %lf\n", end);
    }
    else if (choose == ELEMS)
    {
        FILE *f = fopen(filename, "r+");
        int counter = 0;
        char *tmp = NULL;
        double res = 0;
        double amount_all = 0;
        while ((tmp = read_word_from_file(f)))
        {
            int hash_func_true = *func_hash;
                size_t key;
            if (*func_hash == DEFAULTHASH)
            {
                key = word_to_key(tmp);
            }
            else if (*func_hash == MD5)
            {
                uint8_t result[16];
                md5String(tmp, result);
                key = md_to_string_key(result);
            }
            else
            {
                key = kernigan_to_key(tmp);
            }
            if (hash_func_true != *func_hash)
                *func_hash = hash_func_true;
            int amount = 0;
            clock_t start = clock();
            find_word_new(*table, tmp, key, *func_hash, &amount);
            res += (double) (clock() - start) / CLOCKS_PER_SEC;
            free(tmp);
            amount_all += amount;
            tmp = NULL;
            counter++;
        }
        res = res / counter;
        amount_all = amount_all / counter;
        printf("Количество неповторяющихся элементов %ld\n" , (*table)->count);
        printf("Размер по памяти %ld\n", sizeof(item_t) * (*table)->count);
        printf("Усредненное время поиска всех слов из файла %lf \n", res);
        printf("Усредненное количество сравнений для поиска слова %.3lf \n", amount_all);
    
    }

    return ERR_OK;
}




void dump(tree_t *node)
{
    dump0(node, "", 1, 1);
}

void dump0(tree_t *node, const char* prefix, int root, int last)
{
    if (node != NULL) {
        printf("%s", prefix);
        if (root) {
            printf("└── ");
        } else if (last) {
            printf("├── ");
        } else {
            printf("├── ");
        }
        printf("%s %d\n", node->word, node->counter);

        const char* newPrefix = last ? "    " : "│   ";

        if (node->left != NULL || node->right != NULL) {
            if (node->left != NULL) {
                char* leftPrefix = (char*)malloc(strlen(prefix) + strlen(newPrefix) + 1);
                strcpy(leftPrefix, prefix);
                strcat(leftPrefix, newPrefix);
                dump0(node->left, leftPrefix, 0, node->right == NULL);
                free(leftPrefix);
            }
            if (node->right != NULL) {
                char* rightPrefix = (char*)malloc(strlen(prefix) + strlen(newPrefix) + 1);
                strcpy(rightPrefix, prefix);
                strcat(rightPrefix, newPrefix);
                dump0(node->right, rightPrefix, 0, 1);
                free(rightPrefix);
            }
        }
    }
}

void PrintTree (tree_t *pNode, int n) 
{ 
    if (pNode->left) PrintTree(pNode->left, n+1); 

    for (int i = 0; i < n; i++) printf(" "); 
    printf("%s %d\n", pNode->word, pNode->counter); 

    if (pNode->right) PrintTree(pNode->right, n+1); 
}


void printTree_new(tree_t *root, int level)
{
    if (root == NULL) {
        return;
    }
    printTree_new(root->right, level + 1);
    for (int i = 0; i < level; i++) {
        printf("   ");
    }
    printf("\"%s\" раз - %d\n", root->word, root->counter);
    printTree_new(root->left, level + 1);
}



void print_node_as_dot(tree_t *node, void *param)
{
    FILE *f = param;

    if (node->left)
        fprintf(f, "%s_%d -> %s_%d;\n", node->word, node->counter, node->left->word, node->left->counter);

    if (node->right)
        fprintf(f, "%s_%d -> %s_%d;\n", node->word, node->counter, node->right->word, node->right->counter);
}

void export_tree_to_dot(const char *tree_name, tree_t *tree)
{

    FILE *f = fopen("tree.dot", "w");
    if (!f)
        return;

    fprintf(f, "digraph %s {\n", tree_name);
    fprintf(f, "node [shape=circle, style=filled, color=black, fontcolor=white];\n");

    

    traverse_tree_pre(tree, print_node_as_dot, f);

    fprintf(f, "}\n");

    fclose(f);

    char command[256];
    snprintf(command, sizeof(command), "dot -Tpng tree.dot -o %s", "tree.png");

    // Execute Graphviz command
    int result = system(command);

    if (result != 0)
    {
        fprintf(stderr, "Error executing Graphviz command.\n");
    }
    else
    {
        printf("Tree visualization saved as tree.png\n");
    }
    system("echo 990436 | sudo -S eog tree.png");
}

void traverse_tree_pre(tree_t *tree, void (*f)(tree_t *, void *), void *arg)
{
    if (tree == NULL)
        return;

    f(tree, arg);
    traverse_tree_pre(tree->left, f, arg);
    traverse_tree_pre(tree->right, f, arg);
}

void out_n(FILE *f, node_t *head)
{
    if (head)
    {
        list_print_to_file(f, head);
    }
}