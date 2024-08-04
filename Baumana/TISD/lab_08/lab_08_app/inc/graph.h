#ifndef GRAPH_H_
#define GRAPH_H_

bool is_correct(int **array, size_t n);



void print_g(graph_t *g);

void graph_free(graph_t *graph);

int **matrix_create(graph_t *G);

int fordFulkerson(int **graph, int max, int s, int t);

int find_pos(graph_t *G, node_t *tmp);

bool in_array(graph_t *G, node_t *tmp);

dict_t *init_dict(char *name, size_t *amount);

int dinicMaxFlow(int **graph, int **residualGraph, int *parent, int source, int sink, graph_t *g);

#endif // GRAPH_H_