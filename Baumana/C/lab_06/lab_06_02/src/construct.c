
#include "libmy.h"

#define QUANT 15
#define max(a,b)  (((a)>(b))?(a):(b))
#define min(a,b)  (((a)<(b))?(a):(b))


struct subject items [QUANT];

int check_the_par(char *line)                                                 
{
    for(char *i = line; *i != '\0'; i++)
    {
        if(*i == '/')
        {
            return ERR_BADPAR;
        }
    }
    return ERR_OK;
}

// Поиск подстроки
int substring_search(char *tag, char *name)                                     
{
    size_t count = 0;
    size_t index = 0;
    while( index < strlen(name))
    {
        if(tag[count] == name[index])
        {
            count += 1;
        }
        else 
        {
            count = 0;
        }
        index += 1; 
        if (count == strlen(tag))
        {
            return 0;
        }
    }
    return 1;
}


// Сортировка вставками (устойчивая сортировка)
void insertion_sort(size_t n, struct subject arr[])                             
{
    for(size_t i = 1; i < n; ++i)
    {
        size_t k = i;
        while((k > 0) && (arr[k -1].amount > arr[k].amount))
        {
            struct subject temp = arr[k] ;
            arr[k] = arr[k-1];
            arr[k-1] = temp;   
            k -= 1;        
        } 
    }
}


int lowdens_to_highdens_sort(char *filename)
{
    
    FILE *fp;
    size_t index = 0; 
    
    if(( fp = fopen(filename, "r+")) == NULL )
    {
        fprintf(stdout, "can't open file with name \n");
        
        return ERR_OPEN_FILE;
    }
    
    while((fscanf(fp, "%25s", items[index].name)) == 1)
    {
        
        if ((fscanf(fp, "%lf", &items[index].mass)) != 1)
            return ERR_STR_OVERFLOW;
        if ((fscanf(fp, "%lf", &items[index].amount)) != 1)
            return ERR_NUM_OVERFLOW;
        
        index += 1;

        if (index > QUANT)
            return ERR_STRUCT_OVERFLOW;

    }

    insertion_sort(index, items);
    
    for(size_t b = 0; b < index; b++)
    {
        printf("%s\t\n%lf\t\n%lf\t\n", items[b].name, items[b].mass,items[b].amount);
    }
    
    printf("\n");
    
    fclose(fp);

    return ERR_OK;
}


int all_sort(char *filename)
{

    FILE *fp;
    size_t index = 0; 
    
    if((fp = fopen(filename, "r+")) == NULL)
    {
        fprintf(stdout, "can't open file with name \n");
        return ERR_OPEN_FILE;
    }
    
    while((fscanf(fp, "%25s", items[index].name)) == 1)
    {
        if ((fscanf(fp, "%lf", &items[index].mass)) != 1)
            return ERR_STR_OVERFLOW;
        if ((fscanf(fp, "%lf", &items[index].amount)) != 1)
            return ERR_NUM_OVERFLOW;
        
        index += 1;
        
        if (index > QUANT)
            return ERR_STRUCT_OVERFLOW;

    }

    print_subject(items, index);
    printf("\n");

    return ERR_OK;

}

int substring_sort(char *filename, char *substring)
{

    FILE *fp;
    size_t index = 0;
    // int rc = ERR_OK;

    if ((fp = fopen(filename, "r+")) == NULL)
    {
        fprintf(stdout, "can't open file with name \n");
        return ERR_OPEN_FILE;
    }

    // rc = read_string(fp, items[index].name);
    while((fscanf(fp, "%25s", items[index].name)) == 1)
    {

        if ((fscanf(fp, "%lf", &items[index].mass)) != 1)
            return ERR_STR_OVERFLOW;
        
        if ((fscanf(fp, "%lf", &items[index].amount)) != 1)
            return ERR_NUM_OVERFLOW;
        
        index += 1; 

        if (index > QUANT)
            return ERR_STRUCT_OVERFLOW;

    }
    
    for(size_t i = 0; i < index; ++i)
    {
    
        if(!(substring_search(substring, items[i].name)))
            fprintf(stdout, "%s\t\n%lf\t\n%lf\t\n", items[i].name, items[i].mass, items[i].amount);
    
    }

    return ERR_OK;

}

void show_err_message(int rc)
{

    fprintf(stdout, "Error:\n\t");

    switch(rc)
    {
        case ERR_BADPAR:
            fprintf(stdout, "Невалидные данные командной строки\n");
            break;
    
        case ERR_OPEN_FILE:
            fprintf(stdout, "Невозможно открыть файл\n");
            break;
    
        case ERR_CLOSE_FILE:
            fprintf(stdout, "Невозможно закрыть файл\n");
            break;
    
        case ERR_EMPTY_FILE:
            fprintf(stdout, "Пустой файл\n");
            break;
        
        case ERR_STR_OVERFLOW:
            fprintf(stdout, "Переполнение названия предмета\n");
            break;
    
        case ERR_STRUCT_OVERFLOW:
            fprintf(stdout, "Переполнение количества структур\n");
            break;
    
        case ERR_NUM_OVERFLOW:
            fprintf(stdout, "Переполнение значения числа\n");
            break;

        case ERR_EMPTY_STRING:
            fprintf(stdout, "Ошибка пустой строки\n");
            break;

        case ERR_OK:
            fprintf(stdout, "Программа отработала корректно\n");
            break;

    }

}
