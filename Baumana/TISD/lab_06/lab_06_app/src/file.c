#define _GNU_SOURCE
#include "libmy.h"


int file_check(char *filename)
{
    FILE *f; 
    if (!(f = fopen(filename, "r+")))
        return ERR_OPEN_FILE;
    if (ferror(f))
        return ERR_DATA;
    if (fclose(f))
        return ERR_CLOSE_FILE;
    return ERR_OK;
}

// инициализация имени из файла каждое слово на новой строке
// int read_from_file(FILE *f, tree_t *leaf)
// {
//     char *buf = NULL;
//     size_t len;
//     ssize_t size;
    
//     if ((size = getline(&buf, &len, f)) == -1)
//     {
//         free(buf);
//         return ERR_READ_LINE;
//     }
//     if (buf[strlen(buf) - 1] == '\n')
//         buf[strlen(buf) - 1] = '\0';
    
//     char *tmp = malloc(sizeof(char) * strlen(buf) + 1); 
//     if (!tmp)
//     {
//         free(buf);
//         return ERR_MEM;
//     }
    
//     strcpy(tmp, buf);
//     free(leaf->word);
//     leaf->word = tmp;
//     free(buf);
//     return ERR_OK;    
// }


// считывание одного слова из файла // максимальный размер слова 512
// запись слова в дерево
int read_from_file(FILE *f, tree_t *leaf)
{
    char buf[512];
    if ((fscanf(f, "%512s", buf)) != 1)
        return ERR_READ_LINE;
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
        return ERR_READ_LINE;
    
    char *tmp = malloc(sizeof(char) * (strlen(buf) + 1)); 
    if (!tmp)
        return ERR_MEM;

    strcpy(tmp, buf);
    // free(leaf->word);
    leaf->word = tmp;
    return ERR_OK;    
}


int write_in_file(FILE *f, tree_t *leaf)
{
    if (fprintf(f," %s", leaf->word) != 1)
    {
        return ERR_WRITE_FILE;
    }
    return ERR_OK;
}


int read_file(char *filename, tree_t **tree_head)
{
    FILE *f;
    f = fopen(filename, "r+");
    int rc = ERR_OK;
    *tree_head = leaf_create();
    rc = read_from_file(f, *tree_head);
    tree_t *tail = leaf_create(); 
    if (rc == ERR_OK)
    {
        while ((rc = read_from_file(f, tail)) == ERR_OK)
        {
            tree_t *leaf = leaf_create_with_name(tail);
            // init_leaf(*tree_head, leaf);
            *tree_head = insert(*tree_head, leaf); 
            // free(tail->word);
        }
    }
    // free(tail->word);
    free(tail);
    fclose(f);
    return ERR_OK;
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
