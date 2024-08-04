#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "macros.h"
#include "my_snprintf.h"

char *read_string(char *const dst, char *const src, size_t *pos, size_t max_len)
{
    size_t i = 0;
    for (i = 0; src[i] != '\0'; i++)
    {
        if (*pos + i + 1 < max_len)
            dst[*pos + i] = src[i];
    }

    (*pos) += i;

    return dst;
}

char *hdtoa(char *const dst, short int n)
{
    char *digits = "0123456789";

    size_t pos = 0;
    int neg_flag = 0;
    int num = n;

    if (n < 0)
    {
        neg_flag = 1;
        num = -n;
    }
    else if (num == 0)
        dst[pos++] = '0';

    while (num > 0)
    {
        dst[pos++] = digits[num % 10];
        num = num / 10;
    }

    size_t half = (pos % 2 == 0 ? pos / 2 : pos / 2 + 1);

    for (size_t i = 0; i < half; i++)
    {
        char temp = dst[i];
        dst[i] = dst[pos - i - 1];
        dst[pos - i - 1] = temp;
    }

    if (neg_flag)
    {
        for (int i = pos - 1; i >= 0; i--)
            dst[i + 1] = dst[i];
        dst[0] = '-';

        pos++;
    }

    dst[pos] = '\0';

    return dst;
}

char *copy_string(char *const dst, const char *src, size_t n)
{
    if (!dst || n == 0)
        return dst;

    size_t pos = 0;

    while (src[pos] != '\0' && pos + 1 < n)
    {
        dst[pos] = src[pos];
        pos++;
    }

    dst[pos] = '\0';

    return dst;
}

int my_snprintf(char *s, size_t n, const char *format, ...)
{
    if (!s && n != 0)
        return 0;
    
    char *result = calloc(n, sizeof(char));
    if (!result)
        return 0;
    
    char temp[MAX_STR_LEN];
    size_t pos = 0;

    va_list args;
    va_start(args, format);

    while (*format != '\0')
    {
        if (*format == '%')
        {
            format++;

            switch (*format)
            {
                case 's':
                    read_string(result, va_arg(args, char *), &pos, n);
                    break;
                case 'h':
                    if (*(format + 1) == 'd')
                    {
                        format++;
                        char *strnum = hdtoa(temp, va_arg(args, int));
                        read_string(result, strnum, &pos, n);
                    }
                    else
                        read_string(result, "%", &pos, n);
                    break;
                default:
                    read_string(result, "%", &pos, n);
                    break;
            }
        }
        else
        {
            if (pos + 1 < n)
                result[pos++] = *format;
            else
                pos++;
        }

        format++;
    }

    va_end(args);

    copy_string(s, result, n);

    free(result);

    return (int)pos;
}
