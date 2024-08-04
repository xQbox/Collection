#ifndef IO_H_
#define IO_H_


void print(tree_t *head);

void dump0(tree_t *node, const char* prefix, int root, int last);

void dump(tree_t *node);

void PrintTree (tree_t *pNode, int n);

void apply(tree_t *tree,void (*f)(tree_t*, void*),void *arg);

void print_tree(tree_t *tree_head, int all_size, int start);

void printTree_new(tree_t *root, int level);

void print_node_as_dot(tree_t *node, void *param);

void export_tree_to_dot(const char *tree_name, tree_t *tree);

void traverse_tree_pre(tree_t *tree, void (*f)(tree_t *, void *), void *arg);

int choose(int choice, tree_t **tree_head, char *filename);

void menu_print();

#endif // IO_H_