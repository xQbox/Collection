#include "libmy.h"
void menu_print()
{
    system("clear");
    printf("\nОсновное меню программы\n\t");
    printf("1 - Основная программа + сравнение времени\n\t");
    printf("2 - Вывод стека\n\t");
    printf("3 - Работа со стеком (добавление, удаление элементов, свободные адреса)\n\t");
    printf("4 - Сравнение (по времени, по памяти)\n\t");
    printf("5 - Состояние пустых адресов\n\t");
    printf("0 - Завершение работы программы\n");
}



void print_a(int *a, size_t size)
{
    printf("Массив ->\n");
    for (int i = size - 1; i > -1; --i)
    {
        printf("%d\n", a[i]);
    }
    printf("\n");
}


void print(node_t *node)
{
    printf("Список ->\n");
    for (node_t *cur = node; cur; cur = cur->next)
    {
        printf("%d\n", cur->item);
    }
    printf("\n");
}

void print_add(pointer_t *node)
{
    printf("Список указателей -> \n");
    for (pointer_t *cur = node; cur; cur = cur->next_pointer)
    {
        printf("\t%p\n", (void *) cur->next_node);
    }
    printf("\n");
}

void clear_pointer(pointer_t *head)
{
    pointer_t *tmp;
    while (head)
    {
        tmp = head;
        head = head->next_pointer; 
        free(tmp);
    }
}