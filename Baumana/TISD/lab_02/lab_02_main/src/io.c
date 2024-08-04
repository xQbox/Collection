#include "libmy.h"

void menu_print()
{
    system("clear");
    printf("\nОсновное меню программы\n\t");
    printf("1 - Вывод всей таблицы\n\t");
    printf("2 - Вывод таблицы ключей\n\t");
    printf("3 - Вывод элемента таблицы\n\t");
    printf("4 - Сортировка\n\t");
    printf("5 - Результат эффективности алгоритмов\n\t");
    printf("6 - Добавление элемента таблицы \n\t");
    printf("7 - Удаление элемента таблицы \n\t");
    printf("8 - Cоглашение \n\t");
    printf("0 - Завершнение работы программы\n");
}


int number_check(int *number)
{
    char buff[STRING_SIZE];
    size_t counter = 0;
    printf(">>");
    while (fgets(buff, sizeof(buff), stdin) != NULL)
    {
        counter++;
        if ((strlen(buff) == 2) && ((buff[0] - '0' > -1) && (buff[0] - '0' < 9)))
            break;
        if (counter < 2)
            printf("Ошибка ввода, введите число еще раз: \n");
    }
    *number = buff[0] - '0';
    return  ERR_OK;
}

int data_read(struct data_t *data, FILE *f)
{
    struct data_t temp;
    int rc = ERR_OK;
    if ((rc = line_read(temp.name, f)) == ERR_OK)
    {
        if ((rc = line_read(temp.perfomance, f)) == ERR_OK)
        { 
            if ((rc = price_read(temp.price_range, f)) == ERR_OK)
            { 

                if ((rc = line_read(temp.perfomance_type, f)) == ERR_OK)
                { 
                    if ((strcmp(temp.perfomance_type, "сказка")) == 0)
                    {
                        if ((rc = minage_read(&temp.choose.tale.age, f)) == ERR_OK)
                            data->choose.tale.age = temp.choose.tale.age;
                    }   
                    else if (((strcmp(temp.perfomance_type, "музыкальный")) == 0) || ((strcmp(temp.perfomance_type, "мюзикл")) == 0))                                  
                    {
                        rc = line_read(temp.choose.music.singer, f);
                        if (rc != ERR_OK)
                            return ERR_LINE_READ;
                        rc = line_read(temp.choose.music.country, f);
                        if (rc != ERR_OK)
                            return ERR_LINE_READ;
                        rc = line_read(temp.choose.music.music_type, f);
                        if (rc != ERR_OK)
                            return ERR_LINE_READ;
                        rc = minage_read(&temp.choose.music.age, f);
                        if (rc != ERR_OK)
                            return ERR_LINE_READ;
                        rc = duration_read(&temp.choose.music.duration, f);
                        if (rc != ERR_OK)
                            return ERR_LINE_READ;
                        strcpy(data->choose.music.singer, temp.choose.music.singer);
                        strcpy(data->choose.music.country, temp.choose.music.country);
                        strcpy(data->choose.music.music_type, temp.choose.music.music_type);
                        data->choose.music.age = temp.choose.music.age;
                        data->choose.music.duration = temp.choose.music.duration;
                    }
                } 
            }   
        } 
    }

    if (rc == ERR_OK)
    {
        strcpy(data->name, temp.name);
        strcpy(data->perfomance, temp.perfomance);
        strcpy(data->price_range, temp.price_range);
        strcpy(data->perfomance_type, temp.perfomance_type);
    }
    return rc;
}

int number_read(int *a, FILE *f)
{
    int tmp = 0;
    if ((fscanf(f, "%d\n", &tmp)) != 1)
        return ERR_NUMBER_READ;
    *a = tmp;
    return ERR_OK;
}

int minage_read(size_t *a, FILE *f)
{
    int rc = ERR_OK;
    int tmp;
    if ((rc = number_read(&tmp, f)) == ERR_OK)
    {
        if ((tmp > 0) && (tmp < 100))
        {
            *a = (size_t) tmp;
            return ERR_OK;
        }
    }
    return ERR_RANGE;
}


int line_read(char *string, FILE *f)
{
    char tmp[STRING_SIZE];
    // char new[2];
    if (!(fgets(tmp, sizeof(tmp), f)))
        return ERR_LINE_READ;
    size_t len = strlen(tmp);
    if (tmp[len - 1] == '\n')
    {
        tmp[len - 1] = '\0';
        len--;
    }
    if (!(len))
        return ERR_LINE_SIZE;
    strcpy(string, tmp);   
    return ERR_OK;
}

int price_read(char *string, FILE *f)
{
    char tmp[STRING_SIZE];
    if (line_read(tmp, f) != ERR_OK)
        return ERR_LINE_READ;
    size_t len = strlen(tmp);
    size_t pos = 0;
    for (size_t i = 0; i < len; ++i)
    {
        if ((((tmp[i] - '0') < 0) && ((tmp[i] - '0') > 9)) && (tmp[i] != '-'))
            return ERR_PRICE_READ;
        if (tmp[i] == '-')
            pos = i;
    }
    if ((tmp[0] == '-') || (tmp[len - 1] == '-'))
        return ERR_PRICE_READ;

    int sum_b = 0, sum_a = 0;
    for(size_t i = 0; i < len; ++i)
    {
        if (i < pos)
            sum_b += ((tmp[i] - '0') * pow(10, (pos - i - 1))); 
        else if (i > pos)
            sum_a += ((tmp[i] - '0') * pow(10, (len - i - 1)));
    }
    if (sum_a < sum_b)
        return ERR_PRICE_READ;

    strcpy(string, tmp);
    return ERR_OK;
}


int duration_read(size_t *a, FILE *f)
{
    int rc = ERR_OK;
    int tmp;
    if ((rc = number_read(&tmp, f)) == ERR_OK)
    {
        if ((tmp > 0) && (tmp < 10000))
        {
            *a = (size_t) tmp;
            return ERR_OK;
        }
    }
    return ERR_RANGE;
}



int file_check(char *filename)
{
    FILE *f = fopen(filename, "r");

    if (f == NULL)
        return ERR_FILE_OPEN;

    if (ferror(f) != 0)
        return ERR_FILE_DATA;

    if (fclose(f) == EOF)
        return ERR_FILE_CLOSE;

    return ERR_OK;
}


void print_table(struct data_t *data, int num)
{
    if (num == 0)
    {
        printf("     Индекс  | ");
        printf("     Название театра     | ");
        printf("     Название пьесы     | ");
        printf("     Диапазон цены     | ");
        printf("     Тип пьесы     | ");
        printf("     Минимальный возраст     | ");
        printf("     Страна     | ");
        printf("     Тип мюзикла     | ");
        printf("     Композитор     | "  );
        printf("     Продолжительность     |\n"  ); 
    }
    printf("     %d     |", num);
    printf("     %s  |", data->name);
    printf("     %s   |", data->perfomance);
    printf("     %s   |", data->price_range);
    if ((strcmp(data->perfomance_type, "сказка")) == 0)
    {
        printf("     %s     |", data->perfomance_type);
        printf("     %ld     |\n", data->choose.tale.age);
    }
    else if (((strcmp(data->perfomance_type, "музыкальный")) == 0) || ((strcmp(data->perfomance_type, "мюзикл")) == 0))
    {
        printf("     %s   |", data->perfomance_type);
        printf("     %ld  |", data->choose.music.age);
        printf("     %s   |", data->choose.music.country);
        printf("     %s   |", data->choose.music.music_type);
        printf("     %s   |", data->choose.music.singer);
        printf("     %ld  |\n", data->choose.music.duration);
    }
    else 
    {
        printf("     %s     |\n", data->perfomance_type);
    }
    printf("---------------------------------------\n\n");
}


void print_key_table(struct keys_t *data)
{
    printf("Индекс|");
    printf("Тип пьесы     | ");
    printf("     Минимальный возраст     | ");
    printf("     Страна     | ");
    printf("     Тип мюзикла     | ");
    printf("     Композитор     | "  );
    printf("     Продолжительность     |\n"  ); 
    printf("%d    |", data->index);
    if ((strcmp(data->perfomance_type, "сказка")) == 0)
    {
        printf("     %s     |", data->perfomance_type);
        printf("     %ld     |\n", data->choose.tale.age);
    }
    else if (((strcmp(data->perfomance_type, "музыкальный")) == 0) || ((strcmp(data->perfomance_type, "мюзикл")) == 0))
    {
        printf("     %s   |", data->perfomance_type);
        printf("     %ld  |", data->choose.music.age);
        printf("     %s   |", data->choose.music.country);
        printf("     %s   |", data->choose.music.music_type);
        printf("     %s   |", data->choose.music.singer);
        printf("     %ld  |\n", data->choose.music.duration);
    }
    else 
    {
        printf("     %s     |\n", data->perfomance_type);
    }
    printf("---------------------------------------\n\n");
}

    
void show_err_message(int rc)
{
    fprintf(stdout, "Error:\n\t");
    printf("rc = %d\n\t", rc);
    switch (rc)
    {
        case ERR_NUMBER_READ:
            fprintf(stdout, "Ошибка считывания числа\n");
            break;   
        case ERR_PRICE_READ:
            fprintf(stdout, "Ошибка считывания цены\n");
            break;
        case ERR_LINE_READ:
            fprintf(stdout, "Ошибка считывания строки\n");
            break;   
        case ERR_FILE_OPEN:
            fprintf(stdout, "Невозможно открыть файл\n");
            break;
        case ERR_FILE_CLOSE:
            fprintf(stdout, "Невозможно закрыть файл\n");
            break;
        case ERR_FILE_DATA:
            fprintf(stdout, "Ошибка считывания данныx из файла\n");
            break;
        case ERR_EMPTY_FILE:
            fprintf(stdout, "Ошибка пустой файл\n");
            break;
        case ERR_OK:
            fprintf(stdout, "Программа отработала корректно\n");
            break;
        case ERR_RANGE:
            fprintf(stdout, "Ошибка диапазона значений\n");
            break;
        case ERR_LINE_SIZE:
            fprintf(stdout, "Ошибка длины строки\n");
            break;
        case ERR_BAD_ARG:
            fprintf(stdout, "Ошибка невалидных входных данных командной строки\n");
            break;
        case ERR_SIZE:
            fprintf(stdout, "Ошибка некорректного размера массива\n");
            break;
    }
}

int line_input(char *string)
{
    char buff[STRING_SIZE];
    printf("Введите строку\n>>");
    if(!(fgets(buff, sizeof(buff), stdin)))
        return ERR_LINE_SIZE;
    size_t len = strlen(buff);
    if (buff[len - 1] == '\n')
    {
        buff[len - 1] = '\0';
        len--;
    }
    if (!len)
        return ERR_LINE_SIZE;
    strcpy(string, buff);
    return ERR_OK;
}

int price_input(char *string)
{   
    int num_b, num_a;
    char tmp[2];
    printf("Введите начало диапазона(до 100000)\n>>");
    if (fscanf(stdin, "%d", &num_b) != 1)
        return ERR_PRICE_READ;
    if (num_b > 100000)
        return ERR_RANGE;
    printf("Введите конец диапазона(до 100000)\n>>");
    if (fscanf(stdin, "%d", &num_a) != 1)
        return ERR_PRICE_READ;
    if (num_a > 100000)
        return ERR_RANGE;
    if (num_b > num_a)
        return ERR_RANGE;
    fgets(tmp, sizeof(tmp), stdin);
    sprintf(string, "%d-%d", num_b, num_a);
    return ERR_OK;
}

int number_input(int *number)
{
    int n;
    printf("Введите число\n>>");
    if(fscanf(stdin, "%d", &n) != 1)
        return ERR_NUMBER_READ;
    *number = n;
    return ERR_OK;
}
int minage_input(size_t *number)
{
    int n, rc;
    if ((rc = number_input(&n)) == ERR_OK)
    {
        if ((n > 0) && (n < 100))
        {
            *number = n;
            return ERR_OK;
        }
    }
    return ERR_NUMBER_READ;
}

int duration_input(size_t *number)
{
    int n, rc;
    if ((rc = number_input(&n)) == ERR_OK)
    {
        if ((n > 0) && (n < 10000))
        {
            *number = n;
            return ERR_OK;
        }
    }
    return ERR_NUMBER_READ;
}

int input_delete_parameters(char *string)
{
    int ch, key;
    char n;

    printf("Keys to delete:\n"
           "1 - Название театра\n"
           "2 - Название пьесы\n"
           "3 - Диапазон цены\n"
           "4 - Тип пьесы\n"
           "введите число:\n");

    ch = scanf("%d", &key);
    scanf("%c", &n);

    while (ch != 1 || key < 1 || key > 4)
    {
        printf("Введите число от 1 до 4:\n");
        ch = scanf("%d", &key);
        scanf("%c", &n);
    }
    ch = 0;

    if (key == 1)
    {
        printf("Enter the theatre name:\n");
        fgets(string,  STRING_SIZE, stdin);
        string[strlen(string) - 1] = '\0';
    }
    else if (key == 2)
    {
        printf("Введите название пьесы:\n");
        fgets(string,  STRING_SIZE, stdin);
        string[strlen(string) - 1] = '\0';
    }
    else if (key == 3)
    {
        int number1 = 0, number = 0;
        while (ch != 1 || number < 0 || number1 < 0 || number1 < number)
        {
            printf("Введите мин цену:\n");
            ch = scanf("%d", &number);
            printf("Введите макс цену:\n");
            ch = scanf("%d", &number1);
        }
        sprintf(string, "%d-%d", number, number1);
    }
    else
    {
        {
            printf("Введите тип пьесы:\n");
            fgets(string,  STRING_SIZE, stdin);
            string[strlen(string) - 1] = '\0';
        }
    }

    return key;
}

// int struct_to_arr_read(char *filename, struct data_t *arr);
