#ifndef TREE_H_
#define TREE_H_


int init_leaf(tree_t *tree_head, tree_t *leaf);

tree_t *leaf_create(void);

tree_t *leaf_create_with_name(tree_t *leaf);

tree_t *insert(tree_t *tree, tree_t *node);

void read_tree(tree_t *tree_head);

tree_t *find(tree_t *tree, char *name);

int height_of_tree(tree_t *tree);

void tree_clean(tree_t *tree_head);

tree_t *remove_node(tree_t *tree, char *name);

int HeightOfTree(tree_t * node);

#endif // TREE_H_