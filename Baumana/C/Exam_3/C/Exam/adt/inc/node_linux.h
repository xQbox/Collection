#ifndef NODE_LINUX_H
#define NODE_LINUX_H_

// #define LIST_HEAD_INIT(name) { &(name), &(name) }

// #define LIST_HEAD(name) \
//     lnode_t name = LIST_HEAD_INIT(name)

typedef struct lnode_t lnode_t;
struct lnode_t 
{
    lnode_t *next, *prev;
};

typedef struct data_t data_t;

static inline void INIT_LIST_HEAD(lnode_t *list)
{
    list->next = list;
    list->prev = list;
}

struct data_t
{
    int i;
    lnode_t list;
};

#endif // NODE_LINUX_H_