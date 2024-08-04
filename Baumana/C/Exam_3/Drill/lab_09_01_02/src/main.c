#include "libmy.h"
int main(int argc, char **argv)
{
    if ((argc != 3) && (argc != 2))
        return ERR_ARG_BAD;
    int rc = 0;
    if ((rc = check_file(argv[1])) == ERR_OK)
    {
        size_t size = 0;
        struct item_t *item = NULL;
        if ((rc = ai_init(argv[1], &size, &item)) == ERR_OK)
        {
            if ((rc = ai_create(argv[1], size, item)) == ERR_OK)
            {
                if (argc == 2)
                {
                    sort(item, size);
                }
                else 
                {
                    if (strcmp(argv[2], "ALL") == 0)
                    {
                        for (size_t i = 0; i < size; ++i)
                        {
                            item_print(&item[i]);
                        }
                    }
                    else 
                    {
                        rc = substring_find(argv[2], item, size);
                    }
                }
                ai_free(item, size);
            }
        }
    }
    return rc;
}
