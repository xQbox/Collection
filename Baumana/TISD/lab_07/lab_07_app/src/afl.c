#include "libmy.h"


void count_tree_elems(tree_t *tree, int *amount_of_elems)
{
    if (!tree)
        return;
    count_tree_elems(tree->right, amount_of_elems);
    count_tree_elems(tree->left, amount_of_elems);
    (*amount_of_elems)++;
} 


void init_trees_array(tree_t *tree_head, tree_t **ptr, int *index)
{   
    if (tree_head == NULL)
    {
        return;
    }
    else
    {
        if (tree_head->right != NULL)
        {   
            init_trees_array(tree_head->right, ptr, index);
        }
        if (tree_head->left != NULL)
        {
            init_trees_array(tree_head->left, ptr, index);
        }
        ptr[*index] = tree_head;
        (*index)++;
    }
}

// инициализация массива
tree_t *afl_sort_tree(tree_t *tree, tree_t **ptr, int start_pos, int end_pos)
{
    if (start_pos > end_pos) 
        return NULL;

    int mid = (start_pos + end_pos) / 2;
    tree = ptr[mid];
    tree->left = afl_sort_tree(tree, ptr, start_pos, mid - 1);
    tree->right = afl_sort_tree(tree, ptr, mid + 1, end_pos); 
    return tree;
}   



tree_t *from_bst_afl(tree_t *tree)
{
    int index = 0;
    count_tree_elems(tree, &index);
    tree_t **ptr = (tree_t **) malloc(sizeof(tree_t *) * (index));
    if (ptr)
    {
        for (int i = 0; i < index; ++i)
        {
            ptr[i] = NULL;
        }
        index = 0;
        init_trees_array(tree, ptr, &index);
        
        for (int i = 0; i < index; ++i)
        {
            ptr[i]->left = NULL;
            ptr[i]->right = NULL;
        }

        for (int i = 0; i < index; ++i)
        {
            for (int k = 0; k < index - 1 - i; ++k)
            {
                if ((strcmp(ptr[k]->word, ptr[k + 1]->word)) > 0)
                {
                    tree_t *tmp = ptr[k + 1];
                    ptr[k + 1] = ptr[k];
                    ptr[k] = tmp;
                }
            }
        }
        tree =  afl_sort_tree(tree, ptr, 0, index - 1);
        
        free(ptr);
        return tree;
    }
    // tree_clean(tree);
    return NULL;
}
