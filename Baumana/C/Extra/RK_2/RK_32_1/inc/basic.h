#ifndef BASIC_H_
#define BASIC_H_



int read_from_file(FILE *f, node_t **node);
int init_list_from_file(node_t **list, char *filename, size_t *size_of_list);


int file_check(char *filename);


#endif // BASIC_H_