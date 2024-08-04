#include "libmy.h"


int process(graph_t **graph, char *filename, int choose)
{
    if (choose == INIT)
    {
        filename = filename_create(filename);
        if (filename)
        {
            if (graph)
                graph_free(*graph);
            int rc = init_g_from_file(graph, filename);
            if (!rc)
            {
                printf("Успешно\n");
            }
            else 
            {
                printf("Инициализировать не удалось\n");
            }
        }
        else 
        {
            printf("Неверное названия файла\n");
        }
    }
    else if (choose == PRINT)
    {
        export_tree_to_dot("kaifarik", *graph);
    }
    else if (choose == FORD)
    {
        int **matrix = matrix_create(*graph);
        printf("Доступные вершины\n");
        for (size_t i = 0; i < (*graph)->v; ++i)
        {
            printf("%ld -> %s\n", i + 1, ((*graph)->heads[i]->vertex_name));
        }

        printf("Введите вершины для поиска (исток -> сток)\n");
        int tmp;
        int tmp_n;
        if ((fscanf(stdin, "%d%d", &tmp, &tmp_n)) != 2)
        {
            printf("Ошибка\n");
            return ERR_DATA;
        }
        if (tmp < 0 || (size_t) tmp > (*graph)->v || tmp_n < 0 || (size_t) tmp_n > (*graph)->v)
        {
            printf("Ошибка диапазона\n");
            return ERR_DATA;
        }
        clock_t start = clock();
        int res = fordFulkerson(matrix, (*graph)->v, tmp-1, tmp_n-1); 
        double end = (double) (clock() - start) / CLOCKS_PER_SEC;
        if (res > 3)
            printf("Удалив три дороги разбить граф на компоненты связности Нельзя\n");
        else 
            printf("Удалив три дороги можно разбить граф на компоненты связности\nЗадача решена за %lf\n", end);
        matrix_free(matrix, (*graph)->v);
    }
    else if (choose == BRUTEFORCE)
    {
        // int residualGraph[(*graph)->v][(*graph)->v]; // Остаточная сеть
        // int parent[(*graph)->v]; // Массив для хранения пути
        printf("Доступные вершины\n");
        for (size_t i = 0; i < (*graph)->v; ++i)
        {
            printf("%ld -> %s\n", i + 1, ((*graph)->heads[i]->vertex_name));
        }

        printf("Введите вершины для поиска (исток -> сток)\n");
        int tmp;
        int tmp_n;
        if ((fscanf(stdin, "%d%d", &tmp, &tmp_n)) != 2)
        {
            printf("Ошибка\n");
            return ERR_DATA;
        }
        if (tmp < 0 || (size_t) tmp > (*graph)->v || tmp_n < 0 || (size_t) tmp_n > (*graph)->v)
        {
            printf("Ошибка диапазона\n");
            return ERR_DATA;
        }
        
        int **tmp_k = malloc(sizeof(int *) * (*graph)->v);
        for (size_t i = 0; i < (*graph)->v; ++i)
        {
            tmp_k[i] = calloc((*graph)->v, sizeof(int)); 
        }
        int **matrix = matrix_create((*graph));
        int *parent = malloc(sizeof(int) * (*graph)->v);
        clock_t start = clock();
        int res = dinicMaxFlow(matrix, tmp_k, parent, tmp - 1, tmp_n - 1, *graph);
        double end = (double) (clock() - start) / CLOCKS_PER_SEC;
        if (res > 3)
            printf("Удалив три дороги разбить граф на компоненты связности Нельзя\n");
        else 
            printf("Удалив три дороги можно разбить граф на компоненты связности\nЗадача решена за %lf\n", end);
        matrix_free(matrix, (*graph)->v);
        matrix_free(tmp_k, (*graph)->v);
        free(parent);
    }
    else if (choose == VERTEX)
    {
        printf("Введите данные (Вершина Вершина Стоимость)\n");
        char tmp[26];
        char tmp_n[26];
        int d;
        if ((fscanf(stdin,"%25s%25s%d", tmp, tmp_n, &d)) != 3)
        {
            printf("Ошибка ввода строки\n");
            return ERR_DATA;
        }
        bool flag = false;
        bool flag2 = false;
        for (size_t i = 0; i < (*graph)->v; ++i)
        {
            if ((strcmp(tmp, (*graph)->heads[i]->vertex_name)) == 0)
            {
                for (size_t k = 0; k < (*graph)->v; ++k)
                {
                    if ((strcmp(tmp_n, (*graph)->heads[k]->vertex_name)) == 0)
                    {
                        flag = true;
                        break;
                    }
                }
                node_t *tmp_node = create_node(tmp_n, d);
                node_t *tmp_m = (*graph)->heads[i]->head;
                if (tmp_m == NULL)
                {
                    node_t *head = create_node(tmp_n, 0);
                    head = add_node(head, tmp_node);
                    (*graph)->heads[i]->head = head;
                }
                else 
                {
                    bool tmp_bool = false;
                    while (tmp_m)
                    {   
                        if ((strcmp(tmp_node->vertex_name, tmp_m->vertex_name)) == 0)
                        {
                            tmp_m->way_cost = tmp_node->way_cost;
                            tmp_bool = true;
                            // flag = true;
                            node_free(tmp_node);
                            break;
                        }
                        tmp_m = tmp_m->next;
                    } 
                    if (!tmp_bool)
                    {
                        (*graph)->heads[i]->head = add_node((*graph)->heads[i]->head, tmp_node);
                        // (*graph)->heads[i]->tail = tmp_node->next;
                    }
                }
                
                flag2 = true; 
                break;
            }
        }
        if (!flag)
        {
            if (flag2)
            {
                if ((*graph)->maxamount == (*graph)->v)
                {

                    dict_t **tmp_dict = realloc((*graph)->heads, BLOCK * sizeof(dict_t *));
                    if (!tmp_dict)
                    {
                        printf("Ошибка выделения памяти\n");
                        return ERR_DATA;
                    }  
                    (*graph)->heads = tmp_dict;
                    (*graph)->maxamount += BLOCK;
                    node_t *parte = create_node(tmp_n, 0);
                    (*graph)->heads[(*graph)->lines] = init_dict(tmp_n, &(*graph)->lines);
                    (*graph)->heads[(*graph)->lines - 1]->head = parte; 
                    ((*graph)->v)++;
                }
                else 
                {
                    node_t *parte = create_node(tmp_n, 0);
                    (*graph)->heads[(*graph)->lines] = init_dict(tmp_n, &(*graph)->lines);
                    (*graph)->heads[(*graph)->lines - 1]->head = parte;
                    ((*graph)->v)++;
                }
            }
            else 
            {
                printf("Нельзя добавлять сразу две вершины\n");
            }
        }
    }
    return ERR_OK;
}
