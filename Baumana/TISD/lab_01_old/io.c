#include "libmy.h"
int number_input(char *number)
{
    char M[ARR_LEN - 9];
    char tmp;
    size_t size;
    
    scanf("%c", &tmp);
    printf("Введи целое число (макс. 30 символов): ");
    if ((fgets(M, sizeof(M), stdin)) == NULL) 
        return ERR_IO;
    size = strlen(M);
    if ((size == 1) || (strlen(M) > 30))
        return ERR_RANGE;
    for (size_t i = 0; i < size - 1; i++)
    {
        if ((M[i] < '0') || (M[i] > '9'))
            return ERR_IO;
    }
    strcpy(number, M);
    return ERR_OK;
}


int struct_input(struct long_number_t *long_number)
{
    int rc = ERR_OK;
    char tmp;
    printf("Введите знак мантиссы: ");
    if ((rc = sign_input(&long_number->mantissa_sign)) == ERR_OK)
    {   
        printf("Введите мантиссу (макс. 40 символов): ");
        scanf("%c", &tmp);
        if ((rc = mantissa_input(long_number->mantissa)) == ERR_OK)
        {
            printf("Введите порядoк (в диапозоне от -99999 до 99999): ");
            if (((rc = order_input(&long_number->order)) != ERR_OK))
            {
                return rc;
            }
            return rc;
        }
        return rc;
    }      
    return rc;
}

int order_input(int *order)
{
    if ((scanf("%d", order)) != 1)
        return ERR_IO;
    if ((*order < -99999) || (*order > 99999))
        return ERR_RANGE;
    return ERR_OK;
}
// при вводе подряд - , +  и цифры код работает некорректно
// при вводе ' ошибка сегментации
int sign_input(char *sign)
{
    if ((scanf("%c", sign)) != 1)
        return ERR_IO;
    if ((*sign != '+') && (*sign != '-'))
        return ERR_DATA;
 
    return ERR_OK;
}

int mantissa_input(char *mantissa)
{
    char M[ARR_LEN + 2];
    size_t size, point = 0;
 
    if ((fgets(M, sizeof(M), stdin)) == NULL) 
        return ERR_IO;
    size = strlen(M);
    if ((size == 1) || (strlen(M) > 41))
        return ERR_RANGE;
    for (size_t i = 0; i < size - 1; i++)
    {
        
        if (M[i] == '.')
            point ++;
        if (((M[i] < '0') || (M[i] > '9')) && (M[i] != '.'))
            return ERR_IO;
    }
    if (point > 1)
        return ERR_IO;
    strcpy(mantissa, M);

    return ERR_OK;
}
