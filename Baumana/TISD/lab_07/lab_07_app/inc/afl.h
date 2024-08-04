#ifndef AFL_H_
#define AFL_H_


tree_t *from_bst_afl(tree_t *tree);

void count_tree_elems(tree_t *tree, int *amount_of_elems);

void init_trees_array(tree_t *tree_head, tree_t **ptr, int *index);

tree_t *afl_sort_tree(tree_t *tree, tree_t **ptr, int start_pos, int end_pos);

#endif // AFL_H_