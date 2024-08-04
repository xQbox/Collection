#include "libmy.h"

// 1 пункт меню
int table_print(char *filename)
{
    FILE *f = fopen(filename, "r");
    int rc = ERR_OK;
    struct data_t tmp;
    int i = 0;
    while ((rc = data_read(&tmp, f)) == ERR_OK)
    {
        print_table(&tmp, i);
        ++i;
    }
    fclose(f);
    return rc;
}


// Сортировка вставками (универсальная)
int comp(const void *left, const void *right)
{
    const int *pl = left;
    const int *pr = right;
    return *pl - *pr;
}

void swap(void *left, void *right, size_t elem_size)
{
    char tmp;
    char *pl = left;
    char *pr = right;
    for (size_t i = 0; i < elem_size; i++, pl++, pr++)
    {
        tmp = *pl;
        *pl = *pr;
        *pr = tmp;
    }
}

void insertion_sort(void *data, size_t num, size_t elem_size, int(*comp) (const void *, const void *))
{
    char *ptrs = data;
    char *ptrend = ptrs + (num * elem_size);
    for (char *ps = ptrs + elem_size; ps < ptrend; ps+=elem_size)
    {
        char *ps_n = ps;
        while ((ps_n > ptrs) && (comp(ps_n-elem_size, ps_n) > 0))
        {
            swap(ps_n-elem_size, ps_n, elem_size);
            ps_n-=elem_size;
        }
    }
}

void insertion_sort_base(int *arr, int n)
{
    for (int  i = 1; i < n; ++i)
    {
        int k = i;
        while ((k > 0) && (arr[k - 1] > arr[k]))
        {
            int temp = arr[k - 1];
            arr[k - 1] = arr[k];
            arr[k] = temp;
            k--;
        }
    }
}

// Пузырьковая сортировка для элементов структуры

void mysort(void *data, size_t num, size_t elem_size, int(*comp) (const void *, const void *))
{
    char *ptrs = data;
    char *ptrend = ptrs + (num * elem_size);
    size_t k = 0;
    for(char *ps = ptrs; ps < ptrend; ps+=elem_size)
    {
        for(char *ps_n = ptrs; ps_n < ptrend - elem_size - (elem_size * k); ps_n+=elem_size)
        {
            if(comp(ps_n, ps_n + elem_size) > 0)
            {
                swap(ps_n, ps_n + elem_size, elem_size);
            }
        }
        k += 1; 
    }
}



int comp_name(const void *left, const void *right)
{
    struct data_t pl = *(struct data_t *) left;
    struct data_t pr = *(struct data_t *) right;

    return strcmp(pl.name, pr.name);
}

int comp_perfomance(const void *left, const void *right)
{
    struct data_t pl = *(struct data_t *) left;
    struct data_t pr = *(struct data_t *) right;

    return strcmp(pl.perfomance, pr.perfomance);
}

int comp_perfomance_type(const void *left, const void *right)
{
    struct keys_t pl = *(struct keys_t *) left;
    struct keys_t pr = *(struct keys_t *) right;

    return strcmp(pl.perfomance_type, pr.perfomance_type);
}

int comp_price(const void *left, const void *right)
{
    struct data_t pl = *(struct data_t *) left;
    struct data_t pr = *(struct data_t *) right;
    int sum_pl = 0, sum_pr = 0;
    size_t pl_i = 0;
    size_t pr_i = 0;
    for (; pl.price_range[pl_i] != '-'; ++pl_i);
    for (; pr.price_range[pr_i] != '-'; ++pr_i);
    for (size_t i = 0; pl.price_range[i] != '-'; ++i)
        sum_pl += (pl.price_range[i] - '0') * pow(10, pl_i - i - 1);
    for (size_t i = 0; pr.price_range[i] != '-'; ++i)
        sum_pr += (pr.price_range[i] - '0') * pow(10, pr_i - i - 1);
    return sum_pl - sum_pr;
}

// 4 пункт меню
int sort(char *filename)
{
    int rc =  ERR_OK;
    int choose_sort, choose_key;
    printf("Выберите метод сортировки\n\t1 - сортировка пузырьком\n\t2 - сортировка вставками\n");
    while ((rc = number_check(&choose_sort)) == ERR_OK)
    {
        if ((choose_sort == 1) || (choose_sort == 2))
            break;
        printf("Введите либо 1, либо 2\n");
    }
    printf("Выберите поле , по которому нужно отсортировать таблицу\n\t");
    printf("1 - Название Театра.\n\t2 - Название спектакля.\n\t3 - Диапазон цены(мин->макс).\n");
    while ((rc = number_check(&choose_key)) == ERR_OK)
    {
        if ((choose_key > 0) && (choose_key < 5))
            break;
        printf("Введите число от 1 до 4\n");
    }
    struct data_t arr[ARR_SIZE];
    size_t i = 0;
    FILE *f = fopen(filename, "r+");

    while ((rc = data_read(&arr[i], f)) == ERR_OK)
    {
        ++i;
        if (i > ARR_SIZE - 1)
            break;
    }
    switch (choose_key)
    {
        case 1: 
            if (choose_sort == 1)
            {
                mysort(arr, i, sizeof(struct data_t), comp_name);
            }
            else if (choose_sort == 2)
            {
                insertion_sort(arr, i, sizeof(struct data_t), comp_name);
            }   
            break;
        case 2: 
            if (choose_sort == 1)
            {
                mysort(arr, i, sizeof(struct data_t), comp_perfomance);
            }
            else if (choose_sort == 2)
            {
                insertion_sort(arr, i, sizeof(struct data_t), comp_perfomance);
            }   
            break;
        case 3: 
            if (choose_sort == 1)
            {
                mysort(arr, i, sizeof(struct data_t), comp_price);
            }
            else if (choose_sort == 2)
            {
                insertion_sort(arr, i, sizeof(struct data_t), comp_price);
            }   
            break;

    }
    size_t index = 0;
    while (index < i)
    {
        print_table(&arr[index], index);
        index++;
    }   
    fclose(f);
    return rc;
}


int key(char *filename)
{
    printf("Ключ -> Тип Пьесы\n");
    FILE *f = fopen(filename, "r+");
    struct data_t arr[ARR_SIZE];
    struct keys_t key_arr[ARR_SIZE];
    size_t i = 0, k = 0;
    int rc = ERR_OK;
    while ((rc = data_read(&arr[i], f)) == ERR_OK)
    {
        strcpy(key_arr[k].perfomance_type, arr[i].perfomance_type);
        if (strcmp(arr[i].perfomance_type, "сказка") == 0)
        {
            key_arr[k].choose.tale.age = arr[i].choose.tale.age; 
        }
        else if (((strcmp(arr[i].perfomance_type, "музыкальный")) == 0) || ((strcmp(arr[i].perfomance_type, "мюзикл")) == 0))
        {
            strcpy( key_arr[k].choose.music.singer, arr[i].choose.music.singer);
            strcpy( key_arr[k].choose.music.country, arr[i].choose.music.country);
            strcpy( key_arr[k].choose.music.music_type, arr[i].choose.music.music_type);
            key_arr[k].choose.music.age = arr[i].choose.music.age ;
            key_arr[k].choose.music.duration = arr[i].choose.music.duration;
        }
        key_arr[k].index = i;
        ++i;
        ++k;
        if (i > ARR_SIZE - 1)
            break;
    }
    int choose;
    if (rc == ERR_OK)
        printf("Считывание прошло успешно....\n");
    printf("\nПоказать результат?\n\t1 - да\t2 - нет\n");
    while ((rc = number_check(&choose)) == ERR_OK)
    {    
        if ((choose == 1 )|| (choose == 2))
            break;
        printf("Введите либо 1, либо 2\n");
    }
    if (choose == 1)
    {
        for(size_t m = 0; m < k; ++m)
            print_key_table(&key_arr[m]);
    }
    printf("\nВыберите метод сортировки\n\t1 - сортировка пузырьком\t2 - сортировка вставками\n");
    while ((rc = number_check(&choose)) == ERR_OK)
    {    
        if ((choose == 1 )|| (choose == 2))
            break;
        printf("Введите либо 1, либо 2\n");
    }
    if (choose == 1)
        mysort(key_arr, k, sizeof(struct keys_t), comp_perfomance_type);
    else if (choose == 2)
        insertion_sort(key_arr, k, sizeof(struct keys_t), comp_perfomance_type);
    printf("\n\n");
    printf("Сортировка завершилась....\n");
    printf("\nПоказать результат?\n\t1 - да\t2 - нет\n");
    while ((rc = number_check(&choose)) == ERR_OK)
    {    
        if ((choose == 1 )|| (choose == 2))
            break;
        printf("Введите либо 1, либо 2\n");
    }
    if (choose == 1)
    {
        for(size_t m = 0; m < k; ++m)
            print_key_table(&key_arr[m]);
    }
    printf("\n\n\n\n");
    printf("Вывод исходной таблицы по ключам\n");
    printf("\nПоказать результат?\n\t1 - да\t2 - нет\n");
    while ((rc = number_check(&choose)) == ERR_OK)
    {    
        if ((choose == 1 )|| (choose == 2))
            break;
        printf("Введите либо 1, либо 2\n");
    }
    if (choose == 1)
    {
        for(size_t index = 0; index < i; ++index)
            print_table(&arr[key_arr[index].index], index);
    }
    printf("Пункт завершился.....\n");

    // while(i > 0)
    // {
    //     print_table()
    // }
    fclose(f);
    return rc;
}


int struct_input(char *filename)
{
    int rc = ERR_OK;
    FILE *f = fopen(filename, "a");
    struct data_t temp;
    printf("Название театра\n");
    if ((rc = line_input(temp.name)) == ERR_OK)
    {
        fprintf(f, "%s\n", temp.name);
        printf("Тип спектакля\n");
        if ((rc = line_input(temp.perfomance)) == ERR_OK)
        { 
            fprintf(f, "%s\n", temp.perfomance);
            printf("Ценовой диапазон(от мин к макс)\n");
            if ((rc = price_input(temp.price_range)) == ERR_OK)
            { 
                printf("Тип пьесы\n");
                fprintf(f, "%s\n", temp.price_range);
                if ((rc = line_input(temp.perfomance_type)) == ERR_OK)
                { 
                    fprintf(f, "%s\n", temp.perfomance_type);
                    
                    if ((strcmp(temp.perfomance_type, "сказка")) == 0)
                    {
                        printf("Минимальный возраст\n");
                        if ((rc = minage_input(&temp.choose.tale.age)) == ERR_OK)
                            fprintf(f, "%ld\n", temp.choose.tale.age);
                    }   
                    else if (((strcmp(temp.perfomance_type, "музыкальный")) == 0) || ((strcmp(temp.perfomance_type, "мюзикл")) == 0))                                  
                    {
                        printf("Композитор\n");
                        rc = line_input(temp.choose.music.singer);
                        if (rc != ERR_OK)
                            return ERR_LINE_READ;
                        printf("Страна\n");
                        rc = line_input(temp.choose.music.country);
                        if (rc != ERR_OK)
                            return ERR_LINE_READ;
                        printf("Тип мюзикла\n");
                        rc = line_input(temp.choose.music.music_type);
                        if (rc != ERR_OK)
                            return ERR_LINE_READ;
                        printf("Минимальный возраст\n");
                        rc = minage_input(&temp.choose.music.age);
                        if (rc != ERR_OK)
                            return ERR_LINE_READ;
                        printf("Продолжительность\n");
                        rc = duration_input(&temp.choose.music.duration);
                        if (rc != ERR_OK)
                            return ERR_LINE_READ;
                        fprintf(f, "%s\n", temp.choose.music.singer);
                        fprintf(f, "%s\n", temp.choose.music.country);
                        fprintf(f, "%s\n", temp.choose.music.music_type);
                        fprintf(f, "%ld\n", temp.choose.music.age);
                        fprintf(f, "%ld\n", temp.choose.music.duration);
                    }
                } 
            }   
        } 
    }
    fclose(f);
    return rc;
}

void delete_theatre_by_key(struct data_t *array_theatre, int *array_length, int index)
{
    for (int i = index; i < *array_length; i++)
        array_theatre[i] = array_theatre[i + 1];

    *array_length -= 1;
}


// Меню удаления
void delete_menu(struct data_t *array_theatre, int *array_length)
{
    int key;
    char string[STRING_SIZE];

    key = input_delete_parameters(string);

    for (int i = 0; i < *array_length; i++)
    {
        switch (key)
        {
            case 1:
                if (strcmp(array_theatre[i].name, string) == 0)
                {
                    delete_theatre_by_key(array_theatre, array_length, i);
                    i -= 1;
                }
                break;
            case 2:
                if (strcmp(array_theatre[i].perfomance, string) == 0)
                {
                    delete_theatre_by_key(array_theatre, array_length, i);
                    i -= 1;
                }
                break;
            case 3:
                if ((strcmp(array_theatre[i].perfomance, string)) == 0)
                {
                    delete_theatre_by_key(array_theatre, array_length, i);
                    i -= 1;
                }
                break;
            case 4:
                if ((strcmp(array_theatre[i].perfomance_type, string)) == 0)
                {
                    delete_theatre_by_key(array_theatre, array_length, i);
                    i -= 1;
                }
                break;
        }
    }
}
int struct_delete(char *filename)
{
    int rc = ERR_OK, i = 0;
    FILE *f = fopen(filename, "r");
    struct data_t tmp[ARR_SIZE];
    while ((rc = data_read(&tmp[i], f)) == ERR_OK)
        ++i;
    delete_menu(tmp, &i);
    for (int m = 0; m < i; m++)
    {
        print_table(&tmp[m], m);
    }
    return rc;
}

