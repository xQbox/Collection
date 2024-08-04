#include "libmy.h"


char *input_line(size_t read_quantity)
{
    ssize_t read;
    size_t count = 0;
    char *buf = NULL;
    size_t cur = 0;
    while ((read = getline(&buf, &count, stdin)) != -1)
    {
        cur++;
        if (cur >= read_quantity)
            break;
    } 
    return buf;
}


