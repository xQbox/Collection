#define _GNU_SOURCE
#include "libmy.h"


int read_line_from_file(FILE *f, int *array, size_t n)
{
    ssize_t read; 
    char *buf;
    size_t count, pos;

    buf = NULL, count = 0, pos = 0;

    if ((read = getline(&buf, &count, f)) == -1)
    {
        free(buf);
        return ERR_READ_LINE;
    }
    for (ssize_t i = 0; i < read + 1; ++i)
    {
        printf("%c\n", buf[i]);
        if ((buf[i] == '0') || (buf[i] == '1'))
        {
            if (pos < n)
            {
                array[pos] = buf[i] - 48;
                printf("%d\n", array[pos]);
                ++pos;
            }
        }
    }  

    return ERR_OK;
}



int file_check(char *filename)
{
    FILE *f = fopen(filename, "r+");
    if (!f)
    {
        return ERR_FILE_OPEN;
    }
    if (fclose(f))
        return ERR_CLOSE;
    return ERR_OK;
}




int vertex_input_n(graph_t *G, size_t *cur, FILE *f)
{
    char src[26], dest[26];
    int cost;
    if ((fscanf(f, "%25s%25s%d", src, dest, &cost)) != 3)
        return ERR_DATA;
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
    free(dest_d);
    free(src_d);
    return ERR_OK;
}

int init_g_from_file(graph_t **g, char *filename)
{
    FILE *f;
    f = fopen(filename, "r+");
    int tmp_v = 0, tmp_e = 0;
    if ((fscanf(f, "%d%d", &tmp_v, &tmp_e)) != 2)
        return ERR_DATA;
    if (tmp_v < 1 || tmp_v > 100 || tmp_e < 1 || tmp_e > 10000)
        return ERR_DATA;
    
    size_t v = tmp_v, e = tmp_e;
    /*проверка на корректность данных*/
    for (size_t i = 0; i < e; ++i)
    {
        int d;
        char tmp[256];
        char new[256];  
        if ((fscanf(f, "%25s%25s%d", tmp, new, &d)) != 3)
        {
            if ((strcmp("end", tmp)) == 0)
                break;
            else 
            {
                return ERR_DATA;
            }
        }
    }
    rewind(f);
    fscanf(f, "%*[^\n]");
    *g = create_graph(v, e);
    if (!(*g))
        return ERR_DATA;

    size_t cur;
    int rc;

    cur = 0, rc = 0;
    while ((!(rc = vertex_input_n(*g, &cur, f))))
    {
        ;
    }
    size_t index = 0;
    size_t cur_unique_lines = (*g)->lines;
    while (index < cur_unique_lines)
    {
        node_t *tmp = (*g)->heads[index]->head;
        while (tmp)
        {
            if (!(in_array((*g), tmp)))
            {
                (*g)->heads[(*g)->lines] = init_dict(tmp->vertex_name, &(*g)->lines);
            }
            tmp = tmp->next;
        }
        index++;
    }
    // print_g(*g);
    return ERR_OK;
}



