#define _GNU_SOURCE
#include "io.h"
#define ARR_SIZE 1000
// size_t count_line_in_files(const char *name, ...)
// {

// }

/*
Тестирование функции 
1 пустой файл (0 строк)
2 одна строка (1 - строка)  (test EOF)
3 3---строки 
        - \n (пустая строка)
        - test\n
        - 
4 Слишком большие строки
*/

int count_lines_1(const char *filename, size_t *lines)
{
    FILE *f;
    if (!(f = fopen(filename, "r")))
        return 2;
    char line [ARR_SIZE];
    // size_t count = *lines;
    while ((fgets(line, sizeof(line), f)))
    {
        if (line[strlen(line) - 1] == '\n')
        {
            (*lines)++; 
        }

    }
    
    // if (count == *lines)
    // {
    //     printf("empty file\n");
    //     return 3;
    // }

    if (feof(f))
    {
        return 0;
    }
    else 
    {
        if ((fscanf(f, "%s", line) == 1))
        {
            (*lines)++;
        }
        else 
        {
            return 3;
        }
    }
    return 2;
}




int count_lines_1_owner(const char *filename, size_t *lines)
{
    FILE *f;
    if (!(f = fopen(filename, "r")))
        return 2;
    char line [ARR_SIZE];
    int one_more = 0;
    while ((fgets(line, sizeof(line), f)))
    {
        one_more = 1;
        if (strchr(line, '\n'))
        {
            (*lines)++; 
            one_more = 0;
        }
    }
    if (one_more)
    {
        (*lines)++;
    }
    fclose(f);
    return 0;
}



size_t count_line_in_files(const char *name, ...)
{
    va_list vl;
    va_start(vl, name);
    const char *tmp = name;
    size_t lines = 0, n;
    int rc; 
    while (tmp)
    {
        rc = count_lines_1_owner(name, &n);
        if (!rc)
            lines += n;
        tmp = va_arg(vl, const char *);
    }
    va_end(vl);

    return lines;
}



char *strcat_many(const char *str, ...)
{
    va_list vl;
    va_start(vl, str);
    const char *tmp = str;
    size_t lines = 0;
    while (tmp)
    {
        lines += strlen(tmp);
        tmp = va_arg(vl, const char *);
    }
    char *line = malloc(lines + 1);
    if (!line)
    {
        printf("Ошибка выделения памяти\n");
        va_end(vl);
        return NULL;
    } 
    va_end(vl);

    va_start(vl, str);
    tmp = str;
    int k = 0;
    while (tmp)
    { 
        for (size_t i = 0; i < strlen(tmp); ++i)
        {
            line[k] = tmp[i];
            k++; 
        }
        tmp = va_arg(vl, const char *);
    }
    line[k] = '\0';

    va_end(vl);
    return line;
}

