#ifndef IO_H_
#define IO_H_

struct item_t 
{
    char *item_name;
    double mas;
    double volume;
};

/// Work with struct
int item_create(struct item_t *ptr, char *item_name, double mas, double volume);

void item_print(struct item_t *ptr);

/// File check
int check_file(char *filename);

/// Work with file

int elem_count(char *filename, size_t size, struct item_t *ptr);

int item_read(FILE *f, struct item_t *ptr);

int ai_count(char *filename, size_t *size);


#endif // IO_H_                          
