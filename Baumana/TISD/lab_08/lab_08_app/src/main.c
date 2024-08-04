#include "libmy.h"

int main(void)
{
    graph_t *g = NULL;
    char *filename = NULL;
    init_g_from_file(&g, "new1.txt");
    printf("Программа решает задачу о реберной связности графа для отдельно взятых вершин\n");
    printf("Инициализация файла подразумевает корректные данные\n");
    printf("А именно валидное количество вершин и ребер на первой строчки\n");
    printf("Следующие строчки заполняются в такой последовательности\nВершина Вершина Стоимость\n");
    printf("Открыт файл new.txt\n");
    // graph_free(g);
    char input;
    int choose = -1;
    while (choose != 0)
    {   
        menu();
        fscanf(stdin," %c", &input);
        if (input >= '0' && input <= '5')
        {
            choose = input - '0';
            // printf("choose -> %d\n", choose);
            process(&g, filename, choose);
        }
        scanf("%*[^\n]");
    }
    // graph_t *g = NULL;
    // int rc = init_g_from_file(&g, "new1.txt");
    // printf("%d\n", rc);
    // int **matrix = NULL;
    // matrix = matrix_create(G);
    // print_matrix(matrix, G->v);
    // printf("Максимальный поток из вершины 0 в вершину 5: %d\n", fordFulkerson(matrix, G->v, 0, 2));
    return 0;
}  
