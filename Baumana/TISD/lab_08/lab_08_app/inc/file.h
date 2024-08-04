#ifndef FILE_H_
#define FILE_H_


int read_line_from_file(FILE *f, int *array, size_t n);

int file_check(char *filename);


int init_g_from_file(graph_t **g, char *filename);

#endif // FILE_H_