#ifndef FILE_H_
#define FILE_H_

#include "libmy.h"

int file_check(char *filename);

int read_from_file(FILE *f, tree_t *leaf);

int write_in_file(FILE *f, tree_t *leaf);

int read_file(char *filename, tree_t **tree_head);

int find_in_file(char *filename, char *name);

#endif // FILE_H_