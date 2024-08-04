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

void out(FILE *f, tree_t *head);

void out_n(FILE *f, node_t *head);

void export_tree_to_dot(const char *tree_name, tree_t *tree);

void traverse_tree_pre(tree_t *tree, void (*f)(tree_t *, void *), void *arg);

int choose(int choice, tree_t **tree_head, char *filename, tablec_t **table, size_t *size_of_hashtable, int *func_hash, tablen_t **table_n, size_t *size_of_hashtable_sec, int *hash_func_sec, table_t **table_new, size_t *size_of, int *hash_func_new);
void menu_print();


int choose_hash_func(int choose, tablec_t **table, size_t *size_of_hashtable, int *func_hash, char *filename);
void hashmenu_print();

int choose_hash_list(int choose, tablen_t **table_n, size_t *size_of_hashtable_sec, int *hash_func_sec, char *filename);
void hashlistmenu_print();

int choose_hash_func_two(int choose, table_t **table, size_t *size_of_hashtable, int *func_hash, char *filename);


#endif // IO_H_