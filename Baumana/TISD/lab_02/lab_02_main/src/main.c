#include "libmy.h"

int main(int argc, char **argv)
{
    printf("Что делает программа ?");
    int rc;
    int choose;
    if (argc != 2)
        return ERR_BAD_ARG;
    rc = file_check(argv[1]);
    if (rc != ERR_OK)
        return ERR_EMPTY_FILE;
    do
    {
        menu_print();;
        rc = number_check(&choose);
        
        switch(choose)
        {
            case 1:
                rc = table_print(argv[1]);
                break;
            case 2:
                rc = key(argv[1]);
                break;
            case 3:
                // func_3()
                printf("OK %d ", choose);
                break;
            case 4:
                rc = sort(argv[1]);
                break;
            case 5:
                // func_5()
                printf("OK %d ", choose);
                break;
            case 6:
                struct_input(argv[1]);
                break;
            case 7:
                struct_delete(argv[1]);
                break;
            case 8:
                // func_5()
                printf("OK %d ", choose);
                break;
            
        }
        show_err_message(rc);
        if (choose != 0)
            system(PAUSE);
    }while (choose != 0);
    printf("Спасибо, что воспользовались программой");
    return ERR_OK;
    // return ERR_OK;
}
//     printf("6 - Добавление элемента таблицы \n\t");
//     printf("7 - Удаление элемента таблицы \n\t");