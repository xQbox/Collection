#ifndef LIBMY_H_
#define LIBMY_H_
#define TABLE_SIZE 200
#define ARR_SIZE 20000

enum HASH
{
    DEFAULTHASH,
    MD5,
    KERNIGAN,
};

enum bool
{
    false,
    true,
};

typedef enum bool bool;

enum MENU
{
    EXIT,
    PRINTTREE,
    ADDWORDINTREE,
    ADDWORDINFILE,
    OPENNEWFILE,
    FIND,
    DELETEINTREE,
    DELETEINFILE,
    WORK_WITH_HASHTABLE,
    WORK_WITH_HASHTABLE_LIST,
    WORK_WITH,
};

enum HASHMENU
{
    INITHASHTABLE,
    ADDTOHASH,
    DELETEFROMHASH,
    CHANGEHASHFUNCION,
    RESTRUCTHASH,
    FINDINHASH,
    ELEMS,
    EXITHASH,
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

#include "md5.h"
#include "myerrors.h"
#include "node.h"
#include "hash.h"
#include "hash_table.h"
#include "tree.h"
#include "afl.h"
#include "basic.h"
#include "file.h"
#include "io.h"

#endif // LIBMY_H_