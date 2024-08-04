#include "libmy.h"


void print_matrix(int **array, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t k = 0; k < n; ++k)
        {
            printf("%4d", array[i][k]);
        }
        printf("\n");
    }
}

graph_t *create_graph(size_t v, size_t e)
{
    graph_t *tmp = malloc(sizeof(graph_t));
    if (!tmp)
        return NULL;

    tmp->heads = NULL;
    
    dict_t **tmp_n = (dict_t **) malloc(sizeof(dict_t *) * v); 
    if (!tmp)
        return NULL;
    for (size_t i = 0; i < v; ++i)
        tmp_n[i] = NULL; 
    tmp->lines = 0;
    tmp->v = v; 
    tmp->maxamount = v;
    tmp->e = e;
    tmp->heads = tmp_n;
    return tmp;
}

int vertex_input(graph_t *G, size_t *cur)
{
    char src[26], dest[26];
    int cost;
    printf("Введите данные (Вершина Вершина длина):\n");
    if ((fscanf(stdin,"%25s%25s%d", src, dest, &cost)) != 3)
        return ERR_READ_LINE;
    
    // if ((fscanf(stdin,"%25s", src)) != 1)
    //     return ERR_READ_LINE;
    // printf("%s\n", src);
    // if ((fscanf(stdin,"%25s", dest)) != 1)
    //     return ERR_READ_LINE;
    // printf("%s\n", dest);
    // if ((fscanf(stdin,"%d", &cost)) != 1)
    //     return ERR_READ_LINE;
    
    // printf("%d\n", cost);
    char *src_d =  (char *) malloc(strlen(src) + 1);
    if (!src_d)
        return ERR_DATA;
    strcpy(src_d, src);
   
    char *dest_d =  (char *) malloc(strlen(dest) + 1);
    if (!dest_d)
        return ERR_DATA;
    
    strcpy(dest_d, dest);
    
    
    for (size_t i = 0; i < G->v; ++i)
    {
        if (G->heads[i] != NULL)
        {
            if ((strcmp(G->heads[i]->head->vertex_name, src)) == 0)
            {   
                bool flag = false;
                node_t *tmp = G->heads[i]->head;
                while (tmp->next)
                {
                    if ((strcmp(tmp->vertex_name, dest)) == 0)
                    {
                        tmp->way_cost = cost;
                        flag = true;
                        break;
                    }
                    tmp = tmp->next;
                }
                if (!flag)
                {
                    node_t *tmp_dest = NULL;
                    tmp_dest = create_node(dest_d, cost);
                    tmp->next = tmp_dest;
                    G->heads[i]->tail = tmp_dest->next;
                    (*cur)++;
                    break;
                }
            }
        }
        else 
        {
            // if (G->heads[i] == NULL)
            // {
            
                node_t *head = NULL; 
                node_t *tmp = NULL;
                head = create_node(src_d, 0);
                tmp = create_node(dest_d, cost);
                head = add_node(head, tmp);
                G->heads[i] = create_dict(head, tmp->next, i);
                (G->lines)++;
                (*cur)++;
                break;
            // }
        }
    }
    return ERR_OK;
}


graph_t *input_graph(graph_t *head)
{
    printf("Введите порядок и размер графа (V, E):\n");
    size_t v, e;
    int tmpv, tmpe;
    
    if ((fscanf(stdin, "%d%d", &tmpv, &tmpe)) != 2)
        return NULL;
    if ((tmpv < 0) || (tmpe < 0))
        return NULL;
    printf("%d %d", tmpe, tmpv);
    /*проверка на условия существования графа указанного размера */
    v = tmpv;
    e = tmpe;

    graph_t *G = NULL;

    G = create_graph(v, e);
    if (!G)
        return NULL;

    size_t cur;
    int rc;

    cur = 0, rc = 0;
    while ((!(rc = vertex_input(G, &cur))))
    {
        if (cur >= G->v)
        {
            printf("Все введеено\n");
        }
    }
    printf("rc->%d\n", rc);
    if (rc == ERR_OK)
        head = G;
    else 
    {
        /*очищение памяти из-под списка смежности*/
    }
    size_t index = 0;
    size_t cur_unique_lines = head->lines;
    while (index < cur_unique_lines)
    {
        node_t *tmp = head->heads[index]->head;
        while (tmp)
        {
            if (!(in_array(head, tmp)))
            {
                head->heads[head->lines] = init_dict(tmp->vertex_name, &head->lines);
            }
            tmp = tmp->next;
        }
        index++;
    }

    return head;
}



void menu()
{
    printf("\tМеню программы\n");
    printf("1 - инициализировать новый граф\n");
    printf("2 - вывести граф\n");
    printf("3 - запустить алгоритм Форда-Фалкерсона\n");
    printf("4 - запустить алгоритм полного перебора дорог\n");
    printf("5 - добавить вершину\n");
    printf("0 - завершить\n");
}

char *filename_create(char *name)
{
    fscanf(stdin,"%*[^\n]");
    printf("Введите название файла\n");
    char filename[256];
    if ((fscanf(stdin,"%256s", filename)) != 1)
        return NULL;
    if (filename[strlen(filename) - 1] == '\n')
        filename[strlen(filename) - 1] = 0;
    if ((file_check(filename)))
        return NULL;
    char *tmp = malloc(strlen(filename) + 1);
    if (!tmp)
        return NULL;
    strcpy(tmp, filename);
    name = tmp;
    return name;
}   



void print_in_file(graph_t *g, int **matrix, FILE *f)
{
    for (size_t i = 0; i < g->v; ++i)
    {
        for (size_t k = i; k < g->v; ++k)
        {
            if (matrix[i][k] != 0)
            {
                fprintf(f, "%s -> ", g->heads[i]->vertex_name);
                fprintf(f, "%s\n", g->heads[k]->vertex_name);
                
                // else 
                // {
                //     fprintf(f, "%s, ", g->heads[k]->vertex_name);
                // }
            }
        }
    }
}

void export_tree_to_dot(const char *tree_name, graph_t *g)
{

    FILE *f = fopen("tree.dot", "w");
    if (!f)
        return;
    int **matrix = matrix_create(g);
    fprintf(f, "digraph %s {\n", tree_name);
    fprintf(f, "node [shape=circle, style=filled, color=black, fontcolor=white];\n");

 
    print_in_file(g, matrix, f);
    matrix_free(matrix, g->v);
    fprintf(f, "}\n");

    fclose(f);

    char command[256];
    snprintf(command, sizeof(command), "dot -Tpng tree.dot -o %s", "tree.png");

    // Execute Graphviz command
    int result = system(command);

    if (result != 0)
    {
        fprintf(stderr, "Error executing Graphviz command.\n");
    }
    else
    {
        printf("Tree visualization saved as tree.png\n");
    }
    system("echo 990436 | sudo -S eog tree.png");
}

