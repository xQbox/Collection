#include "libmy.h"
#define ARR_SIZE 5000


int main(void)
{
    printf("Программа считывает целые числа в два стека и сортирует их при помощи третьего стека\n");
    printf("Инициализация стека....\n");
    printf("Введите максимальный размер стека (максимум для реализации статическим массивом 5000)\n");
    size_t max_size;
    int rc = ERR_OK;
    if ((rc = check_number(&max_size)) != ERR_OK)
    {
        printf("Ошибка ввода размера стека\n");
        return rc;
    }          
    node_t *head_first = NULL;
    node_t *head_second = NULL;
    pointer_t *head_free = NULL;
    pointer_t *head_add = NULL;
    int a_first[ARR_SIZE];
    size_t i = 0;
    int a_second[ARR_SIZE];
    size_t j = 0;
    
    char choose;
    printf("Желаете заполнить стек самостоятельно или случайными числами?\n\t1 - Да\n\tДругое - Нет\n>>");
    make_choose(&choose);
    if (choose == '1')
    {
        printf("Инициализация первого списка : \n");
    
        if ((list_init(max_size, &head_first, a_first, &i)) != ERR_OK)
        {
            printf("Ошибка при инициализации первого списка\n");
            return ERR_IO;
        }
        printf("Инициализация второго списка\n");
        if (list_init(max_size, &head_second, a_second, &j) != ERR_OK)
        {
            printf("Ошибка при инициализации второго списка\n");
            return ERR_IO;
        }
    }
    else 
    {
        printf("Инициализация первого списка : \n");
    
        if ((list_init_random(max_size, &head_first, a_first, &i)) != ERR_OK)
        {
            printf("Ошибка при инициализации первого списка\n");
            return ERR_IO;
        }
        printf("Инициализация второго списка\n");
        if (list_init_random(max_size, &head_second, a_second, &j) != ERR_OK)
        {
            printf("Ошибка при инициализации второго списка\n");
            return ERR_IO;
        }
    }

    // void *a_add[ARR_SIZE];
    // size_t l = 0;
    // int a_free[ARR_SIZE];
    // size_t m = 0;  
    node_t *head_third = NULL;
    int a_third[ARR_SIZE];
    size_t k = 0;
    char choose_f;
    int counter = 0;
    int n = 0;
    double time_a_end_full = 0, time_b_end_full = 0;
    size_t size_of_list = 0;
    do
    {
        printf("Введите номер для выбора пункта меню\n>>");
        menu_print();
        // printf("choose -f %c\n", choose_f);
        choose_f = '0';
        scanf(" %c", &choose_f);
        scanf("%*[^\n]");
        switch(choose_f)
        {
            case '1':
                counter++;
                if ((counter > 1) || (i == 0) || (j == 0))
                {
                    printf("Воспользуйтесь четвертым пунктом меню\n");
                    break;
                }
                if (i < 30)
                {
                    printf("\n\nПервый стек имеет вид -->\n");
                    printf("Cписок\n");
                    print(head_first);
                    printf("Массив\n");
                    print_a(a_first, i);
                    printf("\n\nВторой стек имеет вид -->\n");
                    printf("Cписок\n");
                    print(head_second);
                    printf("Массив\n");
                    print_a(a_second, j);
                }

                clock_t time_a, time_b;
                double time_a_end, time_b_end;
                
                time_a = clock();
                head_third = towers(head_first, head_second, head_third);
                time_a_end = (double) (clock() - time_a) / CLOCKS_PER_SEC;
                
                time_b = clock();
                tower_a(a_first, &i, a_second, &j, a_third, &k);
                time_b_end = (double) (clock() - time_b) / CLOCKS_PER_SEC; 
                
                if (k < 50)
                {
                    print(head_third);

                    print_a(a_third, k);
                }
                printf("Время сортировки стэка (список) -> %lf\n Время сортировки стэка (массив) -> %lf\n", time_a_end, time_b_end);
                printf("Размер в байтах для реализации списком (%ld) Размер в байтах при реализации массивом(%ld) \n", k * 4, max_size * 4 * 3 );
                
                clear(head_third);
                break;
            case '2':
                if (i == 0 || j == 0)
                {
                    printf("Сначала инициализируйте стеки\n");
                    break;
                }
                second(a_first, i, a_second, j, head_first, head_second);
                break;
            case '3':
                if (counter > 0)
                {
                    head_first = NULL;
                    head_second = NULL;
                    head_third = NULL;
                    head_free = NULL;
                    head_add = NULL;
                    k = 0;
                    counter = 0;
                }
                third(&head_first, &head_second, a_first, &i, a_second, &j, max_size, &head_free, &head_add);
                break;
            case '4':
                printf("Сортировка стека \n");
                while (n < 100)
                {
                    node_t *head_first_f = NULL;
                    node_t *head_second_f = NULL;
                    int a_first_f[ARR_SIZE];
                    size_t i_f = 0;
                    int a_second_f[ARR_SIZE];
                    size_t j_f = 0;
                    list_init_random(max_size, &head_first_f, a_first_f, &i_f);
                    list_init_random(max_size, &head_second_f, a_second_f, &j_f);
                    node_t *head_third_f = NULL;
                    int a_third_f[ARR_SIZE];
                    size_t k_f = 0;

                    clock_t time_a_f, time_b_f;
                    
                    time_a_f = clock();
                    head_third_f = towers(head_first_f, head_second_f, head_third_f);
                    time_a_end_full += (double) (clock() - time_a_f) / CLOCKS_PER_SEC;
                    
                    time_b_f = clock();
                    tower_a(a_first_f, &i_f, a_second_f, &j_f, a_third_f, &k_f);
                    time_b_end_full += (double) (clock() - time_b_f) / CLOCKS_PER_SEC; 
                    clear(head_third_f);
                    size_of_list = k_f;
                    n++;
                }
                time_a_end_full /= n;
                time_b_end_full /= n;
                n = 0;
                printf("Время сортировки списка  -> %lf\n Время сортировки массива -> %lf\n", time_a_end_full, time_b_end_full);
                printf("Размер в байтах для реализации списком (%ld) Размер в байтах при реализации массивом(%ld) \n", size_of_list * 4, max_size * 4 * 3 );
                
                time_a_end_full = 0;
                time_b_end_full = 0;
                break;
            case '5':
                fifth(a_first, i, a_second, j, max_size, head_free, head_add);
                break;
        }
        if (choose_f != '0')
        {
            char tmp;
            printf("Введите символ для продолжения\n>>");
            scanf(" %c", &tmp);
            scanf("%*[^\n]");
        }
    }while (choose_f != '0');
    if (head_first)
        clear(head_first);
    if (head_second)
        clear(head_second);
    if (head_free)
        clear_pointer(head_free);
    if (head_add)
        clear_pointer(head_add);
    printf("Спасибо, что воспользовались программой\n");
    return ERR_OK;
}

