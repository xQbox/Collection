#include "libmy.h"


int main(void)
{
    {
        printf("Тест на ввод мантиссы: \n");
        int rc;
        size_t point_position = ARR_LEN * 2;
        char mantissa[ARR_LEN + 3];
        rc = mantissa_input(mantissa, &point_position);
        if (rc != ERR_OK)
            printf("Error\n");
        else 
            printf("OK\n");
        printf("Код возврата -> %d\n", rc);
    }
    {
        printf("Тест на ввод порядка: \n");
        int rc;
        int order;
        rc = order_input(&order);
        if (rc != ERR_OK)
            printf("Error\n");
        else
            printf("OK\n");
        printf("Код возврата -> %d\n", rc);
    }
    {
        printf("Тест на приведение числа к нормализованному виду: \n");
        struct long_number_t number;
        char M[] = ".123456789";
        strcpy(number.mantissa, "123456789.");
        number.order = 33;
        int order = (int) (strlen(M) - 1) + number.order, rc; 
        size_t point_position = strlen(number.mantissa) - 1;
        rc = normalized_number(number.mantissa, &number.order, &point_position);
        if ((strcmp(number.mantissa, M) != 0) || (order != number.order))
        {
            printf("Error\n");
        }
        printf("OK\n");
        printf("Код возврата -> %d\n", rc); 
    }
    {
        char tmp;
        scanf("%c", &tmp);
        printf("Тест на ввод числа: \n");
        int rc;
        char mantissa[ARR_LEN + 2];
        rc = number_input(mantissa);
        if (rc != ERR_OK)
            printf("Error\n");
        else 
            printf("OK\n");
        printf("Код возврата -> %d\n", rc);
    }
    return ERR_OK;
}