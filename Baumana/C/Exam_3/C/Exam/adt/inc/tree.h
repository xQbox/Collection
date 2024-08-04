#ifndef TREE_H_
#define TREE_H_

typedef struct tree_t tree_t;

struct tree_t
{
    char *str;
    tree_t *left;
    tree_t *right;
};

tree_t *create_leaf(char *buf);

tree_t *create_tree(tree_t *tree, tree_t *leaf);

void free_leaf(tree_t *leaf);
void free_tree(tree_t *head);

tree_t *add_leaf(tree_t *tree, tree_t *leaf);

tree_t *remove_leaf(tree_t *tree, tree_t *leaf);
tree_t *find_min(tree_t *tree);

void apply(tree_t *head, void (*app)(tree_t *, void *), void *arg);

int height_of_tree(tree_t *tree);

int create_tree_from_input(tree_t **head_n);


void print_leaf(tree_t *head, void *arg);

#endif // TREE_H_