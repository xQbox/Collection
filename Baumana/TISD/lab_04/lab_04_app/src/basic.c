#include "libmy.h"
#define ARR_SIZE 5000

void print_b(node_t *node)
{
    for (node_t *cur = node; cur; cur = cur->next)
    {
        printf("This is number %d\n", cur->item);
    }
}

void make_choose(char *choose)
{
    fscanf(stdin," %c", choose);
    fscanf(stdin, "%*[^\n]"); 
}

int check_number(size_t *number)
{
    int tmp;
    printf(">>");
    if (fscanf(stdin, "%d", &tmp) != 1)
    {
        return ERR_NUM_INPUT;
    }
    if ((tmp > 5000) || (tmp < 1))
    {
        return ERR_RANGE;
    }
    *number = tmp;
    return ERR_OK;
}

/*
    Алгоритм перестановки неустойчивый //TODO
    Создание одного списка на основе двух других
    по сравнению минимального верхнего элемента списка (стека)
    -----------------------------------------------------------------
    Алгоритм сортировки двух стеков по возрастанию с помощью третьего 
    - не работает с одинаковыми числами (исправлено)
    - не устойчивый
*/
node_t *towers(node_t *head_first, node_t *head_second, node_t *head_third)
{
    size_t flag = 0;        
    while (flag == 0)
    {
        flag = 1;
        node_t *tmp = NULL;
        // Этап 1: формирование 1-го списка
        if (!head_third)
        {
            if (head_first->item >= head_second->item)
            {
                node_t *tmp = head_second->next;
                head_second->next = NULL;
                head_third = head_second;
                head_second = tmp;
            }
            else if (head_first->item <= head_second->item)
            {
                tmp = head_first->next;
                head_first->next = NULL;
                head_third = head_first;
                head_first = tmp;
            }
        }
        while (head_first || head_second)
        {
            if (head_second && head_first)
            {        
                if (head_first->item <= head_second->item)
                {
                    tmp = head_first->next;
                    head_first->next = head_third;
                    head_third = head_first;
                    head_first = tmp;
                }
                else if (head_second->item <= head_first->item)
                {
                    tmp = head_second->next;
                    head_second->next = head_third;
                    head_third = head_second;
                    head_second = tmp;
                }               
            }
            else if (head_second)
            {
                    while (head_second)
                    {
                        tmp = head_second->next;
                        head_second->next = head_third;
                        head_third = head_second;
                        head_second = tmp; 
                    }
            }
            else if (head_first)
            {   
                while (head_first)
                {
                    tmp = head_first->next;
                    head_first->next = head_third;
                    head_third = head_first;
                    head_first = tmp;
                }        
            }
        }
        node_t *cur = head_third;
        node_t *next = cur->next;
        while (cur->next)
        {
            if (cur->item < next->item)
            {
                flag = 0;
            }
            cur = cur->next;
            next = next->next; 
        }

        // printf("Third list ->\n");
        // print_b(head_third);
        // printf("First list ->\n");
        // print_b(head_first);
        // printf("Second list -> \n");
        // print_b(head_second);
        // printf("Flag->%ld\n", flag);
        if (flag == 1)
        {
            return head_third;
        }
        // Этап 2 : формирование 3(2) списков по правилу
        // Только меньшие элементы кладутся на большие
        // 2.1 формирование одного списка (меньшее на большее)
        // Инициализация 
        tmp = head_third->next;
        head_third->next = head_first;
        head_first = head_third;
        head_third = tmp; 
        while (head_third)
        {
            if (head_third->item <= head_first->item)
            {
                tmp = head_third->next;
                head_third->next = head_first;
                head_first = head_third;
                head_third = tmp;
            }
            else 
            {
                break;
            }
        }
        if (head_third)
        {
            tmp = head_third->next;
            head_third->next = head_second;
            head_second = head_third;
            head_third = tmp;
            while (head_third)
            {   
                node_t *tmp = head_third->next;
                if (head_third->item <= head_first->item )
                {    
                    head_third->next = head_first;
                    head_first = head_third;
                }
                else if (head_third->item <= head_second->item)
                {
                    head_third->next = head_second;
                    head_second = head_third;
                }
                else 
                {
                    break;
                }
                head_third = tmp;
            }
        }
        else 
        {
            // Первый список упорядочен в обратном порядке
            return head_first;
            break;
        }
    }
    return head_third;
}

void tower_a(int *a_first, size_t *i, int *a_second, size_t *j, int *a_third, size_t *k)
{
    size_t flag = 0;
    while(flag == 0)
    {
        flag = 1;
        while(*j != 0 || *i != 0)
        {   
            if (*j != 0 && *i != 0)
            {
                if (a_first[*i - 1] <= a_second[*j - 1])
                {
                    a_third[*k] = a_first[*i - 1];
                    (*i)--;
                    (*k)++;
                }
                else if (a_first[*i - 1] >= a_second[*j - 1])
                {
                    a_third[*k] = a_second[*j - 1];
                    (*j)--;
                    (*k)++;
                }
            }
            else if (*j != 0)
            {
                while (*j != 0)
                {
                    a_third[*k] = a_second[*j - 1];
                    (*j)--;
                    (*k)++;
                }
            }
            else if (*i != 0)
            {
                while (*i != 0)
                {
                    a_third[*k] = a_first[*i - 1];
                    (*i)--;
                    (*k)++;
                }
            }
        }
        size_t index = 0;
        while (index < *k - 1)
        {
            if (a_third[index] > a_third[index + 1])
            {
                flag = 0;
            }
            index++;
        }
        if (flag == 1)
        {
            break;
        }
        
        a_first[*i] = a_third[*k - 1];
        (*k)--;
        (*i)++;

        while (a_third[*k - 1] <= a_first[*i - 1])
        {
            a_first[*i] = a_third[*k - 1];
            (*i)++;
            (*k)--;
        }
        if (*k != 0)
        {
            a_second[*j] = a_third[*k - 1];
            (*j)++;
            (*k)--;
            while (*k != 0)
            {
                if (a_third[*k - 1] <= a_first[*i - 1])
                {
                    a_first[*i] = a_third[*k - 1];
                    (*k)--;
                    (*i)++;
                }
                else if (a_third[*k - 1] <= a_second[*j - 1])
                {
                    a_second[*j] = a_third[*k - 1];
                    (*k)--;
                    (*j)++;
                }
                else 
                {
                    break;
                }
            }
        }
        else 
        {
            printf("Первый массив отсоритрован в обратном порядке\n");
            break;
        }
    }   
}


void second(int *a_first, size_t i, int *a_second, size_t j, node_t *head_first, node_t *head_second)
{
    printf("Состояние первого стека\n");
    print_a(a_first, i);
    print(head_first);
    printf("Состояние второго стека\n");
    print_a(a_second, j);
    print(head_second);
}

int third(node_t **head_first, node_t **head_second, int *a_first, size_t *i, int *a_second, size_t *j, size_t maxim, pointer_t **head_free, pointer_t **head_add)
{
    printf("Работа со стеком ( время для первого , адреса для второго)\n\t1 - Добавление элемента\n\t2 - Удаление элемента\n\t3 - Свободные адреса стека\n\tДругое - пропуск\n>>");
    char choose;
    fscanf(stdin, " %c", &choose);
    scanf("%*[^\n]");
    if (choose == '1')
    {
        char choose_n;
        printf("Введите номер стека для работы\n\t1 - Первый\n\t2 - Второй\n>>");
        fscanf(stdin, " %c", &choose_n);
        scanf("%*[^\n]");
        if (choose_n == '1')
        {
            if (*i >= maxim)
            {
                printf("Превышен размер стека\n");
                return ERR_RANGE;
            }
            int tmp;
            printf("Введите число для записи в стек\n>>");
            if ((fscanf(stdin, "%d", &tmp)) != 1)
            {
                printf("Ошибка ввода числа\n");
                return ERR_NUM_INPUT;
            }
            node_t *tmp_node;
            clock_t time_arr_start, time_list_start;
            double time_arr, time_list;
            time_list_start = clock();
            tmp_node = node_create(tmp);
            *head_first = add(tmp_node, *head_first);
            time_list = (double) (clock() - time_list_start) / CLOCKS_PER_SEC;
            time_arr_start = clock();
            a_first[*i] = tmp;
            (*i)++;
            time_arr = (double) (clock() - time_arr_start) / CLOCKS_PER_SEC;
            printf("Время для добавления в стек: \n1) на списке -> %lf\n2) на массиве -> %lf\n", time_list, time_arr);
            printf("Число успешно записано\n");
        }
        else if (choose_n == '2')
        {
            if (*j > maxim)
            {
                printf("Превышен размер стека\n");
                return ERR_RANGE;
            }
            int tmp;
            
            printf("Введите число для записи в стек\n>>");
            
            if ((fscanf(stdin, "%d", &tmp)) != 1)
            {
                printf("Ошибка ввода числа\n");
                return ERR_NUM_INPUT;
            }
        
            node_t *tmp_node;
            tmp_node = node_create(tmp);
            *head_second = add(tmp_node, *head_second);
            a_second[*j] = tmp;
            (*j)++;
            pointer_t *tmp_p;
            tmp_p = pointer_create(*head_second);
            *head_add = add_pointer(tmp_p, *head_add);
            printf("Добавленный адрес-> %p\n", (void *) (*head_add)->next_node);
            printf("Число успешно записано\n");
        }
        else 
        {
            printf("Неопределенный ввод\n");
            return ERR_NUM_INPUT;
        }
    }
    else if (choose == '2')
    {
        char choose_n;
        
        printf("Введите номер стека для работы\n\t1 - Первый\n\t2 - Второй\n>>");
        fscanf(stdin, " %c", &choose_n);
        scanf("%*[^\n]");
        
        if (choose_n == '1')
        {
            if (*i == 0)
            {
                printf("Стек пуст\nУдалить невозможно\n");
                return ERR_EMPTY;
            }
            clock_t time_arr_start, time_list_start;
            double time_arr, time_list;
            time_list_start = clock();
            clear_node(head_first);
            time_list = (double) (clock() - time_list_start) / CLOCKS_PER_SEC;
            time_arr_start = clock();
            (*i)--;
            time_arr = (double) (clock() - time_arr_start) / CLOCKS_PER_SEC;
            printf("Время для удаления элемента  стека: \n1) на списке -> %lf\n2) на массиве -> %lf\n", time_list, time_arr);
            printf("Удаление успешно\n");
        }
        else if (choose_n == '2')
        {

            if (*j == 0)
            {
                printf("Стек пуст\nУдалить невозможно\n");
                return ERR_EMPTY;
            }

            pointer_t *tmp_p;
            tmp_p = pointer_create(*head_second);
            *head_free = add_pointer(tmp_p, *head_free);
            clear_node(head_second);
            (*j)--;
            printf("Очищенный адрес -> %p\n\n", (void *) (*head_free)->next_node);
            printf("Удаление успешно\n");
        }
        else 
        {
            printf("Неопределенный ввод\n");
            return ERR_NUM_INPUT;
        }
    }
    else if (choose == '3')
    {
        forth(*i, *j, maxim);
    }
    else 
    {
        printf("Пункт меню завершен\n");
        return ERR_OK;
    }
    return ERR_OK;
}

void forth(size_t i, size_t j, size_t maxim)
{
    printf("Количество свободных ячеек памяти для первого стека %ld\n", maxim - i);
    printf("Количество свободных ячеек памяти для второго стека %ld\n", maxim - j);
}


void fifth(int *a_first, size_t i, int *a_second, size_t j, size_t maxim, pointer_t *head_free, pointer_t *head_add)
{
    printf("Показать свободные адреса в стеке:\n\t1 - Первом\n\t2 - Втором\n\tДругое - Пропустить\n>>");
    char choose;
    scanf(" %c", &choose);
    scanf("%*[^\n]");
    if (choose == '1')
    {
        for (size_t index = i; index < maxim; index++)
        {
            printf("%p\n", (void *) (a_first + index * sizeof(int)));
        }
    }
    else if (choose == '2')
    {
        for (size_t index = j; index < maxim; index++)
        {
            printf("%p\n", (void *) (a_second + index * sizeof(int)));
        }
        printf("Очищенные указатели\n");
        print_add(head_free);
        printf("Добавленные указатели\n");
        print_add(head_add);
    }
    else 
    {
        printf("Неопределенный ввод\n");
    }        
}

