#include "libmy.h"

int read_from_file(FILE *f, node_t **node)
{
    char surname[MAX_SURNAME + 1];
    if (!(fgets(surname, sizeof(surname), f)))
        return ERR_READ_LINE;
    if (surname[strlen(surname) - 1] == '\n')
        surname[strlen(surname) - 1] = '\0';
    if ((strlen(surname)) == 0)
    {
        return ERR_LINE_SIZE;
    }

    int year;
    if ((fscanf(f, "%d\n", &year)) != 1)
        return ERR_NUMBER_READ;
    if ((year < 1830) || (year > 2023))
        return ERR_YEAR_RANGE;  
    
    char group[MAX_GROUP];
    if (!(fgets(group, sizeof(group), f)))
        return ERR_NUMBER_READ;
    if (group[strlen(group) - 1] == '\n')
        group[strlen(group) - 1] = '\0';
    if ((strlen(group)) == 0)
    {
        return ERR_LINE_SIZE;
    }
    *node = create(surname, year, group);
    if (!node)
    {
        return ERR_MEM;
    }
    return ERR_OK;
}   

int init_list_from_file(node_t **list, char *filename, size_t *size_of_list)
{
    FILE *f = fopen(filename, "r+");
    node_t *head = NULL;
    int rc = ERR_OK;
    if ((rc = read_from_file(f, &head)))
    {
        return rc;
    }
    (*size_of_list)++;
    // printf("%s", head->surname);
    node_t *node = NULL; 
    while (!(rc = read_from_file(f, &node)))
    {
        head = push(head, node);
        (*size_of_list)++;
    }
    if ((rc == ERR_READ_LINE) && (feof(f)))
        rc = ERR_OK;
    if (rc == ERR_OK)
    {
        *list = head;
    }
    else 
    {
        list_free(head);
    }
    return rc;
}

int file_check(char *filename)
{
    FILE *f = fopen(filename, "r+");
    if (!f)
    {
        return ERR_FILE_OPEN;
    }
    return ERR_OK;
}

// void sort(node_t )