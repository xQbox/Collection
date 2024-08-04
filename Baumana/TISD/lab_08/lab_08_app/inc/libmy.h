#ifndef LIBMY_H_
#define LIBMY_H_



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define BLOCK 10

enum bool
{
    false,
    true,
};

/// меню программы
enum menu
{
    EXIT,
    INIT,
    PRINT,
    FORD,
    BRUTEFORCE,
    VERTEX,
};

typedef struct node_t node_t;

struct node_t 
{
    char *vertex_name;  // название вершины 
    int way_cost;       // стоимость прохода по пути
    node_t *next;       // указатель на следующий элемент
};


typedef struct dict_t dict_t;

struct dict_t 
{
    char *vertex_name;         // название вершины 
    int i;                     // позиция в массиве смежности
    node_t *head;              // указатель на начало списка смежности
    node_t *tail;              // указатель на хвост для добавления в список смежности
};


typedef struct graph_t graph_t;

struct graph_t
{
    size_t lines;   // количество уникальных строк
    size_t v;       //  порядок графа (количество вершин)
    size_t e;       // размер графа (количество ребер)
    size_t maxamount;  // количество выделенной памяти под массив указателей
    dict_t **heads; // массив указателей на голову списка
};


typedef enum bool bool;

#include "myerrors.h"
#include "node.h"
#include "graph.h"
#include "io.h"
#include "file.h"
#include "menu.h"
#include "time.h"

#endif // LIBMY_H_