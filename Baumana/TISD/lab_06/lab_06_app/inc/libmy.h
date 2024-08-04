#ifndef LIBMY_H_
#define LIBMY_H_

#define ARR_SIZE 20000

enum MENU
{
    PRINTTREE,
    ADDWORDINTREE,
    ADDWORDINFILE,
    OPENNEWFILE,
    FIND,
    DELETEINTREE,
    DELETEINFILE,
    EXIT,
};


struct tree_t 
{
    int counter;     // - количество повторений
    char *word;     // - слово  
    struct tree_t *right; // - указатель на правое  дерево
    struct tree_t *left; // - указатель на левое дерево
};

typedef struct tree_t tree_t;


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>
#include <unistd.h>

#include "myerrors.h"
#include "file.h"
#include "io.h"
#include "tree.h"
#include "basic.h"

#endif // LIBMY_H_