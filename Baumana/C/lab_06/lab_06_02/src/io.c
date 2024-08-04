
#include "libmy.h"

int file_check(char *filename)
{
    FILE *fp;
    if((fp = fopen(filename, "r+")) == NULL)
    {
        return ERR_OPEN_FILE;
    }
    if(ferror(fp) != 0)
    {
        return ERR_DATA;
    }
    if(fclose(fp) == EOF)
    {
        return ERR_CLOSE_FILE;
    }

    return ERR_OK;
}

int print_subject(struct subject *items, size_t number)
{
    for(size_t i = 0 ; i < number; ++i)
    {
        fprintf(stdout,"%s\t\n%lf\t\n%lf\t\n", items[i].name, items[i].mass, items[i].amount);
    }

    return ERR_OK;
}



int read_string(FILE *fp, char *name)
{

    if(fscanf(fp, "%25s", name) != 1)
    {
        if((*name =='\0') || (*name == '\n'))
            return ERR_EMPTY_STRING; 
        
        return ERR_STR_OVERFLOW;
    }
    return ERR_OK;

}


int read_number(FILE *fp, double *number)
{

    if(fscanf(fp, "%lf", number) != 1)
    {   
        if(*number < 0)
            return ERR_IO;
        
        return ERR_NUM_OVERFLOW;
    }

    return ERR_OK;

}
