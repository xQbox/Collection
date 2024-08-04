#define _GNU_SOURCE
#include "libmy.h"
#define STRING_SIZE 256

int item_create(struct item_t *ptr, char *item_name_one, double mas_one, double volume_one)
{
    char *ptrs = malloc(strlen(item_name_one) + 1);   
    if (ptrs)
    {
	    free(ptr->item_name);
        strcpy(ptrs, item_name_one);
       	ptr->item_name = ptrs;
        ptr->mas = mas_one;
        ptr->volume = volume_one;
        return ERR_OK;
    }
    else 
        return ERR_MEM;
}

void item_print(struct item_t *ptr)
{
    printf("%s\n%lf\n%lf\n", ptr->item_name, ptr->mas, ptr->volume);
}


int check_file(char *filename)
{
    FILE *f;
    f = fopen(filename, "r");
    if (!f)
        return ERR_OPEN_FILE;
    if (ferror(f))
        return ERR_OPEN_FILE;
    if (fclose(f) == EOF)
        return ERR_CLOSE_FILE;
    return ERR_OK;
}

// проблема со считыванием строки больше 256

int item_read(FILE *f, struct item_t *ptr)
{
    char tmp[2];
    char *item_name = NULL;
    double mas, volume;
    size_t len = 0;
    ssize_t read;
    if ((read = getline(&item_name, &len, f)) == -1)
    {
        free(item_name);
        return ERR_STRING;
    }
    if (item_name[strlen(item_name) - 1] == '\n')
    {
        item_name[strlen(item_name) - 1] = '\0';
        if ((strlen(item_name) == 0))
        {
            free(item_name);
            return ERR_STRING;
        }
    }
    if (read > 0)
    {
        if (fscanf(f, "%lf", &mas) != 1)
        {
            free(item_name);
            return ERR_MAS;
        }
        if (fscanf(f, "%lf", &volume) != 1)
        {
            free(item_name);
            return ERR_VOLUME;
        }
        if ((volume < 0) || (mas < 0))
        {
            free(item_name);
            return ERR_DATA;
        }
        fgets(tmp, sizeof(tmp), f);
        // {
        //     free(item_name);         
        //     return ERR_ENDSTRING;
        // } 
        item_create(ptr, item_name, mas, volume);
        free(item_name);
        return ERR_OK;
    }
    return ERR_MEM;
}


int elem_count(char *filename, size_t size, struct item_t *ptr)
{
    FILE *f; 
    size_t tmp = size; 
    f = fopen(filename, "r");
    int rc = ERR_OK;
    while ((rc = item_read(f, ptr)) == ERR_OK)
        size++;
    
    // printf("rc ->%d", rc);
    if (feof(f))
        rc = ERR_OK;
    if (size == tmp)
        rc = ERR_EMPTY_FILE;
    free(ptr->item_name);
    fclose(f);
    return rc;
}

int ai_count(char *filename, size_t *size)
{
    FILE *f; 
    size_t size_tmp = *size; 
    struct item_t tmp = {NULL, 0, 0};
    f = fopen(filename, "r");
    int rc = ERR_OK;
    while ((rc = item_read(f, &tmp)) == ERR_OK)
        (*size)++;
    // printf("rc ->%d", rc);
    if (feof(f) && rc == ERR_STRING)
        rc = ERR_OK;
    
    // printf("rc ->%d", rc);
    if (*size == size_tmp)
        rc = ERR_EMPTY_FILE;
    free(tmp.item_name);
    fclose(f);
    return rc;
}

 