#ifndef IO_H_
#define IO_H_

void print_matrix(int **array, size_t n);

void menu();

char *filename_create(char *name);

graph_t *create_graph(size_t v, size_t e);
graph_t *input_graph(graph_t *head);

void export_tree_to_dot(const char *tree_name, graph_t *g);

#endif // IO_H_