#include "libmy.h"


bool is_correct(int **array, size_t n)
{
    size_t total, odd;

    total = 0, odd = 0;
    for (size_t i = 0; i < n; ++i)
    {
        int sum = 0;
        for (size_t k = 0; i < n; ++k)
        {
            if (array[i][k] != 0)
                sum++;
        }
        total += sum;
        if (sum % 2 == 1)
            odd++;  
    } 
    
    if ((total % 2 == 0) || (total < n))
        return false;

    if (odd % 2 != 0)
        return false;
    return true;
}


bool in_array(graph_t *G, node_t *tmp)
{
    for (size_t i = 0; i < G->lines; ++i)
    {
        if ((strcmp(tmp->vertex_name, G->heads[i]->vertex_name)) == 0)
            return true;
    }
    return false;
}

dict_t *init_dict(char *name, size_t *amount)
{
    dict_t *tmp = malloc(sizeof(dict_t));
    char *tmp_name = malloc(strlen(name) + 1);
    
    if (!tmp_name)
        return NULL;
    
    if (!tmp)
    {
        free(tmp_name);
        return NULL;
    }
    strcpy(tmp_name, name);
    tmp->head = NULL;
    tmp->tail = NULL;
    tmp->i = *amount;
    tmp->vertex_name = tmp_name;
    (*amount)++;
    return tmp;
}

int find_pos(graph_t *G, node_t *tmp)
{
    for (size_t i = 0; i < G->v; ++i)
    {
        if ((strcmp(G->heads[i]->vertex_name, tmp->vertex_name)) == 0)
            return G->heads[i]->i;
    }
    return -1;
}


int **matrix_create(graph_t *G)
{  
    int **matrix = (int **) malloc(sizeof(int *) * G->v);
    if (!matrix)
        return NULL;
    for (size_t i = 0; i < G->v; ++i)
    {
        matrix[i] = calloc(G->v, sizeof(int));
    }
    printf("%ld\n", G->v);
    size_t index = 0;
    size_t cur_unique_lines = G->lines;
    while (index < cur_unique_lines)
    {
        node_t *tmp = G->heads[index]->head;
        while (tmp)
        {
            if (!(in_array(G, tmp)))
            {
                G->heads[G->lines] = init_dict(tmp->vertex_name, &G->lines);
            }
            tmp = tmp->next;
        }
        index++;
    }
    for (size_t i = 0;i < G->lines; ++i)
    {
        printf("%s\n", G->heads[i]->vertex_name);
    }
    for (size_t i = 0; i < G->v; ++i)
    {
        if (G->heads[i]->head != NULL)
        {
            node_t *tmp = G->heads[i]->head;
            while (tmp)
            {
                if (tmp->way_cost != 0)
                {
                    matrix[i][find_pos(G, tmp)] = 1;
                    matrix[find_pos(G, tmp)][i] = 1;
                }
                tmp = tmp->next;
            }
        }
    }
    return matrix;
}
    
void dict_free(dict_t *tmp)
{
    if (tmp)
    {
        free(tmp->vertex_name);
        // free(tmp->tail);
        // free(tmp->head);
        free(tmp);
    }
}

void graph_free(graph_t *graph)
{
    for (size_t i = 0; i < graph->v; ++i)
    {
        list_clear(graph->heads[i]->head);   
        dict_free(graph->heads[i]);
    }
    free(graph->heads);
    free(graph);
}

void print_g(graph_t *g)
{
   for (size_t i = 0; i < g->v; ++i)
    {
        if (g->heads[i] != NULL)
        {
            node_t *tmp = g->heads[i]->head;
            while (tmp)
            {
                printf("%d, %s\n", tmp->way_cost, tmp->vertex_name);
                tmp = tmp->next;
            }
            printf("123444s\n");
        }
    }
}




bool bfs(int **rGraph, int max, int s, int t, int parent[]) {
    bool visited[max];
    for (int i = 0; i < max; i++) {
        visited[i] = false;
    }

    int queue[max];
    int front = 0, rear = 0;
    queue[rear++] = s;
    visited[s] = true;
    parent[s] = -1;

    while (front != rear) {
        int u = queue[front++];
        for (int v = 0; v < max; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                queue[rear++] = v;
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return (visited[t] == true);
}

int fordFulkerson(int **graph, int max, int s, int t)
{
    int u, v;
    int **rGraph = malloc(sizeof(int *) * max);
    for (int i = 0; i < max; ++i)
    {
        rGraph[i] = calloc(max, sizeof(int));
    }
    for (u = 0; u < max; u++) {
        for (v = 0; v < max; v++) {
            rGraph[u][v] = graph[u][v];
        }
    }

    int parent[max];
    int max_flow = 0;

    while (bfs(rGraph, max, s, t, parent)) {
        int path_flow = __INT32_MAX__;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = path_flow < rGraph[u][v] ? path_flow : rGraph[u][v];
        }
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }

    return max_flow;
}





#define V 6 // Количество вершин в графе

int graph[V][V]; // Граф в виде матрицы смежности

// Функция для поиска кратчайшего пути в остаточной сети с использованием BFS
bool bfs_n(int *parent, int **residualGraph, int s, int t, graph_t *g) 
{
    bool visited[g->v];
    for (size_t i = 0; i < g->v; i++) 
    {
        visited[i] = false;
    }

    visited[s] = true;
    parent[s] = -1;

    int queue[g->v];
    int front = 0, rear = 0;
    queue[rear++] = s;

    while (front != rear) 
    {
        int u = queue[front++];
        for (size_t v = 0; v < g->v; v++) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                queue[rear++] = v;
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return visited[t];
}

// Функция для нахождения максимального потока в графе
int dinicMaxFlow(int **graph, int **residualGraph, int *parent, int source, int sink, graph_t *g) 
{
    int maxFlow = 0;

    // Инициализируем остаточную сеть
    for (size_t u = 0; u < g->v; u++) {
        for (size_t v = 0; v < g->v; v++) {
            residualGraph[u][v] = graph[u][v];
        }
    }

    // Находим увеличивающий путь и увеличиваем поток, пока увеличивающий путь существует
    while (bfs_n(parent, residualGraph, source, sink, g)) {
        int pathFlow = g->v+1;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = (pathFlow < residualGraph[u][v]) ? pathFlow : residualGraph[u][v];
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

