#ifndef IO_H_
#define IO_H_

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

size_t count_line_in_files(const char *name, ...);

int count_lines_1(const char *filename, size_t *lines);

char *strcat_many(const char *str, ...);

int count_lines_1_owner(const char *filename, size_t *lines);

int count_lines_2(const char *filename, size_t *lines);

#endif // IO_H_