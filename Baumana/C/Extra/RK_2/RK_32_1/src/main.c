#include "libmy.h"

int main(int argc, char **argv)
{

    int rc = ERR_OK;
    if (argc == 2)
    {
        node_t *tmp = NULL;
        rc = file_check(argv[1]);
        size_t size = 0;
        if (rc == ERR_OK)
            rc = init_list_from_file(&tmp, argv[1], &size);
        if (rc == ERR_OK)
        {
            // list(tmp);
            // list_free(tmp);  
            node_t **tmp_list = malloc((size) * sizeof(node_t *));
            
            if (tmp_list)
            {
                for (size_t i = 0; i < size; ++i)
                {
                    tmp_list[i] = NULL;
                }
                node_t *new_head = tmp;
                for (size_t i = 0; i < size ; ++i)
                {
                    tmp_list[i] = new_head;
                    new_head = new_head->next;
                }
                // printf("\n\n\n");
                for (int i = (int) size - 1; i > -1; --i)
                {
                    printf("%s\n %d\n %s\n", tmp_list[i]->surname, tmp_list[i]->year, tmp_list[i]->group);
                }
            }
            
            list_free(tmp);            
            free(tmp_list);
        }
    }
    else
    { 
        printf("Передайте валидное название файла в аргументы командной строки\n");
        rc = OPEN_FILE_FIRST;
    }
    return rc;
}