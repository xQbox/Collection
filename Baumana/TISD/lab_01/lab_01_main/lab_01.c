#include "libmy.h"

int main(void)
{

    int rc;
    printf("Программа умножает вещественное число ( 40 символов ) на целоe ( 30 символов )\n\n");
    struct long_number_t mantissa;
    if ((rc = base(&mantissa)) == ERR_OK)
        return ERR_OK;
    show_err_message(rc);
    return rc;
}