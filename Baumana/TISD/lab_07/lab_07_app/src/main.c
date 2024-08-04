#include "libmy.h"
#define ARR_SIZE 20000

int main(void)
{   
    {
        printf("Программа создает частотный словарь на основе файла\n");
        printf("Открыт файл text.txt\n");
        printf("Стандартный размер таблиц: 50 \n");
        tree_t *tree_head = NULL;
        read_file("text.txt", &tree_head);
        // int *hash_func = malloc(sizeof(int));
        // *hash_func = 0;
        int hash_func = 0;
        int hash_func_sec = 0;
        int hash_func_th = 0;
        size_t size_of_hashtable = 50;
        size_t size_of_hashtable_second = 50;
        size_t size_of_hashtable_new = 50;
        tablec_t *table = init_hashtable_from_file("text.txt", size_of_hashtable, hash_func);
        tablen_t *tmp_list = init_hashtablen_from_file("text.txt", size_of_hashtable, hash_func_sec);
        table_t *tmp_node = init_hashtable_from_file_new("text.txt", size_of_hashtable_new, hash_func_th);
        char *filename = "text.txt";
        int choice = -1;
        // char out;
        char tmp;
        // int choice_exit = -1;
        char free_space[2];
        while (tmp != 'e')
        {
            menu_print();
            choice = -1;
            if ((fscanf(stdin, " %c", &tmp)) == 1)
            {
                scanf("%*[^\n]");

                fgets(free_space, sizeof(free_space), stdin);
                if (tmp >= '0' && tmp <= '9')
                {
                    sscanf(&tmp, "%d", &choice);
                    choose(choice, &tree_head, filename, &table, &size_of_hashtable, &hash_func, &tmp_list, &size_of_hashtable_second, &hash_func_sec, &tmp_node, &size_of_hashtable_new, &hash_func_th);
                }
                else if (tmp == 'h')
                {
                    choice = 10;
                    choose(choice, &tree_head, filename, &table, &size_of_hashtable, &hash_func, &tmp_list, &size_of_hashtable_second, &hash_func_sec, &tmp_node, &size_of_hashtable_new, &hash_func_th);
                
                }
                else 
                {
                    continue;
                }
            }
            // printf("Выйти - 0\n");
            // fscanf(stdin, " %c", &out);
            // sscanf(&out, "%d", &choice_exit);
            // scanf("%*[^\n]");
        }
        hashtablec_delete(table);
        tree_clean(tree_head);
        hashtablen_delete(tmp_list);
    }
    return ERR_OK;
}
