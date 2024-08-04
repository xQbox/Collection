#include <string.h>
#include <stdlib.h>
#include "book.h"


#define BUF_SIZE    128


int book_init(struct book_t *pbook, const char *title, int year)
{
    char *ptmp = strdup(title);

    if (ptmp)
    {
        free(pbook->title);

        pbook->title = ptmp;
        pbook->year = year;

        return ERR_OK;
    }

    return ERR_MEM;
}


int book_copy(struct book_t *pdst, const struct book_t *psrc)
{
    return book_init(pdst, psrc->title, psrc->year);
}


void book_free_content(struct book_t *pbook)
{
    free(pbook->title);
    pbook->title = NULL;
}


int book_read(FILE *f, struct book_t *pbook)
{
    char   buf[BUF_SIZE + 8];
    size_t len;
    char   tmp[16];
    int    year;

    if (!fgets(buf, sizeof(buf), f))
        return ERR_IO;

    len = strlen(buf);
    if (len && buf[len - 1] == '\n')
    {
        buf[len - 1] = '\0';
        len--;
    }

    if (!len || len > BUF_SIZE)
        return ERR_DATA;

    if (fscanf(f, "%d", &year) != 1)
        return ERR_IO;

    if (year < 0)
        return ERR_DATA;

    fgets(tmp, sizeof(tmp), f);

    return book_init(pbook, buf, year);
}


int book_read_ex(FILE *f, struct book_t *pbook)
{
    char    *buf = NULL;
    size_t  len = 0;
    ssize_t read;
    int     year;
    int     rc = ERR_IO;

    if ((read = getline(&buf, &len, f)) == -1)
    {
        // !!!
        free(buf);
        return rc;
    }

    if (read)
    {
        if (fscanf(f, "%d\n", &year) == 1)
        {
            if (year >= 0)
                rc = book_init(pbook, buf, year);
            else
                rc = ERR_DATA;
        }
        else
            rc = ERR_IO;
    }
    else
        rc = ERR_DATA;

    free(buf);

    return rc;
}


void book_print(FILE *f, const struct book_t *pbook)
{
    fprintf(f, "%s\n", pbook->title);
    fprintf(f, "%d\n", pbook->year);
}


int book_cmp_by_title(const void *l, const void *r)
{
    const struct book_t *pl = l;
    const struct book_t *pr = r;
    
    return strcmp(pl->title, pr->title);
}


int book_cmp_by_year(const void *l, const void *r)
{
    const struct book_t *pl = l;
    const struct book_t *pr = r;
    
    return pl->year - pr->year;
}
