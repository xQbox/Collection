#include "libmy.h"


int struct_input(struct long_number_t *number)
{
    int rc = ERR_OK;
    size_t point_position = ARR_LEN * 2;
    printf("Введите мантиссу ( знак по умол. + , макс 40 символов)\n>+---------1---------2---------3---------4---------5\n");
    if (((rc = mantissa_input(number->mantissa, &point_position)) != ERR_OK))
        return ERR_MANT_IO;
    // проверка на наличие вещественного числа 
    // (если нет \. устанавливается в последнюю позицию)
    if (point_position == ARR_LEN * 2)
    {
        if ((number->mantissa[strlen(number->mantissa) - 1] == '\n'))
        {
            point_position = strlen(number->mantissa) - 1;
            number->mantissa[strlen(number->mantissa) - 1] = '.';
        }
        else
        {    
            point_position = strlen(number->mantissa);
            number->mantissa[strlen(number->mantissa) + 1] = 0; 
        }
    }
    // урезание вводимой мантиссы на 1 символ (\n)
    if (number->mantissa[strlen(number->mantissa) - 1] == '\n')
        number->mantissa[strlen(number->mantissa) - 1] = 0;
   
    printf("Введите порядок ( знак по умол. + , макс 5 цифр)\n");
    if ((rc = order_input(&number->order)) != ERR_OK)
        return ERR_MANT_IO;
    if ((rc = normalized_number(number->mantissa, &number->order, &point_position)) != ERR_OK)
        return ERR_MANT_IO;
    
    printf("\nИтоговое число:\n>+---------1---------2---------3---------4---------5\n  %s E %d\n", number->mantissa, number->order);
    return ERR_OK;
}


int mantissa_input(char *mantissa, size_t *point_position)
{
    char M[ARR_LEN + 10];
    size_t len, sign_position,
    count_sign = 0, count_point = 0, index = 0, pend = 0; //point, flag; позиция точки зависит от размера массива
    if ((fgets(M, sizeof(M), stdin)) == NULL)
        return ERR_MANT_IO;
    len = strlen(M);
    pend = len - 1;
    // Проверка строки на корректность ввода и позицию ( цифры \+ \- \. )
    for (size_t i = 0; i < len - 1; i++)
    {
        if (((M[i] < '0') || (M[i]) > '9') && (M[i] != '.') && ((M[i] != '+') && (M[i] != '-')))
            return ERR_IO;
        if (M[i] == '.')
        {
            *point_position = i; 
            count_point += 1;
        }
        if ((M[i] == '+') || (M[i] == '-'))
        {
            count_sign += 1;
            sign_position = i;
        }
    }
    if ((count_sign > 1) || (count_point > 1))
        return ERR_IO;
    if (count_sign == 1)
    {
        if (sign_position != 0)
            return ERR_IO;
    }

    // Проверка на количество считанных символов
    // Проверка на правильную последовательность цифр
    if (*point_position != ARR_LEN * 2)
    {    // Пока не достигнет значимой цифры (первой) 
        while (((!(isdigit(M[index])) || (M[index] == '0')) && (index < *point_position))) // && (index < len))
        {
            index ++;
        }
        while (((!(isdigit(M[pend])) || (M[pend] == '0')) && (pend > *point_position)))// && (pend > 0))
        {
            pend --;
        }
        if ((len - 1 - (pend - index)) > ARR_LEN + 2)
            return ERR_IO; 
        char N[ARR_LEN + 3];
        size_t i = 0;
        if (M[0] == '-')
        {
            N[i] = M[0];
            i += 1;
        }
        printf("\nНезначащие нули будут удалены.\nУдаление...\n\n");
        for (; index < pend + 1; i++, index++)
            N[i] = M[index];
        N[i] = 0; 
        if (((strlen(N) == 2) && (N[0] == '-')) || (strlen(N) == 1))
            return ERR_DATA;
        strcpy(mantissa, N);
        return ERR_OK;
        
    }

    // сделать проверку для целых чисел
    // пограничный случай с размером 1 (0001000)
    while ((M[index] == '0') || (M[index] == '+') || (M[index] == '-'))
    {
        index ++;
    }
    if ((len - 1 - index) > ARR_LEN + 2)
            return ERR_IO; 
    
    char N[ARR_LEN + 2];
    size_t i = 0;
    if (M[0] == '-')
    {
        N[i] = M[0];
        i += 1;
    }
    printf("\nНезначащие нули будут удалены.\nУдаление...\n\n");
    for (;index < len; i++, index++) // изменен диапозон с len - 1 до len
        N[i] = M[index];
    N[i] = 0; 
    if (((strlen(N) == 1)) || ((strlen(N) == 2) && (N[0] == '-')))
        return ERR_DATA;
    strcpy(mantissa, N);
    return ERR_OK;
}

int order_input(int *order)
{
    if ((scanf("%d", order)) != 1)
        return ERR_IO;
    if ((*order > 99999) || (*order < -99999))
        return ERR_RANGE;
    return ERR_OK;
}

int number_input(char *number)
{
    char M[ARR_LEN - 9];
    size_t len, index = 0, sign_position, count_sign = 0; 
    printf("\nВведите целое число ( знак по умол. + , макс 30 цифр )\n>+---------1---------2---------3---------4---------5\n");

    if ((fgets(M, sizeof(M), stdin)) == NULL)
        return ERR_IO;
    len = strlen(M);
    if ((M[0] == '\n') || (M[0] == 0))
        return ERR_IO;
    if (M[len - 1] == '\n')
        M[len - 1] = 0;
    for (size_t i = 0; i < strlen(M); i++)
    {
        if (((M[i] < '0') || (M[i]) > '9') && ((M[i] != '+') && (M[i] != '-')))
            return ERR_IO;
        if ((M[i] == '+') || (M[i] == '-'))
        {
            count_sign += 1;
            sign_position = i;
        }
    }
    if (count_sign > 1)
        return ERR_IO;
    if (count_sign == 1)
    {
        if (sign_position != 0)
            return ERR_IO;
    }
    while ((M[index] == '0') || (M[index] == '+') || (M[index] == '-'))
    {
        index ++;
    }
    if ((strlen(M) - index) > (ARR_LEN - 8)) // изменен диапозон с  ARR_LEN - 8 до ARR_LEN - 10
        return ERR_IO;                 // Можно добавить + 1 k index чтобы обрезаьб знак

    char N[ARR_LEN - 9];
    size_t i = 0;
    if (M[0] == '-')
    {
        N[i] = M[0];
        i += 1;
    }
    printf("\nНезначащие нули будут удалены.\nУдаление...\n");
    for (;index < strlen(M); i++, index++) // изменен диапозон с len - 1 до len
        N[i] = M[index];
    N[i] = 0; 
    if ((N[0] == '\n') || (N[0] == '\0') || ((strlen(N) == 0) || ((N[0] == '-') && strlen(N) == 1)))
        return ERR_RANGE; 
    strcpy(number, N);
    return ERR_OK;
}                            


void show_err_message(int rc)
{
    fprintf(stdout, "Error:\n\t");
    switch (rc)
    {
        case ERR_BADPAR:
            fprintf(stdout, "\nНевалидные данные командной строки\n");
            break;   
        case ERR_NUMBER:
            fprintf(stdout, "\nОшибка невалидного ввода номера\n");
            break;
        case ERR_EMPTY_STRING:
            fprintf(stdout, "\nОшибка пустой строки\n");
            break;
        case ERR_OVERFLOW:
            fprintf(stdout, "\nОшибка переполнения массива структур\n");
            break;
        case ERR_RANGE:
            fprintf(stdout, "\nОшибка диапозона значений\n");
            break;
        case ERR_MANT_IO:
            fprintf(stdout, "\nОшибка ввода мантиссы\n");
            break;
        case ERR_POINT:
            fprintf(stdout, "\nПозитивный исход с точкой\n");
            break;
        case ERR_DATA:
            fprintf(stdout, "\nОшибка данных\n");
            break;
        case ERR_IO:
            fprintf(stdout, "\nОшибка ввода / вывода\n");
            break;
        case ERR_OK:
            fprintf(stdout, "\nПрограмма отработала корректно\n");
            break;
    }
}              



                            ///часть 1 для проверки вещественного числа и уменьшения размера занимаемой памяти

                            // if (index > 1 || (pend + 1 < len - 1))
                            // {


                            // }
                            // printf("I AM HERE real number index < 2\n");
                        
                            // printf("\n%ld\n", len);
                            // if (((strlen(M)) == 2 && (M[0] = '.')) ||
                            // (strlen(M) == 3 && ((M[0] == '-') || (M[0] == '+') || M[0] == '0')))
                            //     return ERR_DATA;
                            
                            // strcpy(mantissa, M);
                            // printf("\n%s\n", mantissa);
                            // return ERR_OK;

                            // часть 2 для проверки и уменьшения размера занимаего места
                            // if (index > 0) // изменен диапозон значений (с 1  на 0)
                            // {
                            /*// }
                            // printf("I AM HERE regular number index < 2\n"); 
                            // printf("\n%ld\n", len);
                            // if (((strlen(M)) == 2 && (M[0] == '0')) || (strlen(M) == 0))
                            //     return ERR_DATA;

                            // strcpy(mantissa, M);
                            // printf("\n%s\n", mantissa);
                            // return ERR_OK; */

                            // проверка размерности считанной строки
                            // if ((mantissa[0] == '\n') || mantissa[0] == '\0')
                            //     return ERR_IO;
                            // if (mantissa[len - 1] == '\n')
                            //     mantissa[len - 1] = '\0';



