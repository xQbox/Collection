#include <stdio.h>
#include <string.h>
#include "libmy.h"


int main(int argc, char **argv)
{
    int rc;
    if ( (argc <= 1) || ( argc >= 4 ) )
    {
        printf(" syntax : \n\t --help or \n\t FILE.NAME and \n\t PREFIX \n");
        return ERR_BADPAR ;
    }

    if ( argv[2] == NULL )
    {
        rc = lowdens_to_highdens_sort(argv[1]);
    }
    else if (!(strcmp(argv[2], "ALL")))
    {
        rc = all_sort(argv[1]);
    }
    else 
    {
        rc = substring_sort(argv[1], argv[2]);
    }
    show_err_message(rc);
    // (void) rc;
    return 0;
}
