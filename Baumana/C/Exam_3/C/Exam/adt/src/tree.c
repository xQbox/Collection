#include "libmy.h"

void free_leaf(tree_t *leaf)
{
    free(leaf->str);
    free(leaf);
}

void print_leaf(tree_t *head, void *arg)
{
    printf("%s", head->str);
}

tree_t *create_leaf(char *buf)
{
    if (!buf)
        return NULL;
    char *tmp = malloc(strlen(buf) + 1);
    if (!tmp)
    {
        free(buf);
        return NULL;
    }
    char end;
    sscanf(buf, "%c", &end);
    if (end == '\n')
    {
        free(buf);
        return NULL;
    }
    tree_t *leaf = malloc(sizeof(tree_t));
    if (!leaf)
    {
        printf("MEM ERROR\n");
        free(buf);
        free(tmp);
        return NULL;
    }
    strcpy(tmp, buf);
    leaf->str = tmp;
    leaf->left = NULL;
    leaf->right = NULL;
    return leaf;
}

tree_t *create_tree(tree_t *tree, tree_t *leaf)
{
    if (!tree)
    {
        return leaf;
    }
    int cmp = strcmp(tree->str, leaf->str);
    if (cmp == 0)
        free_leaf(leaf);
    else if (cmp > 0)
        tree->left = create_tree(tree->left, leaf);
    else
        tree->right = create_tree(tree->right, leaf);

    return tree;
}

tree_t *find_leaf(tree_t *tree, tree_t *leaf)
{
    if (!tree)
        return NULL;
    int cmp = strcmp(tree->str, leaf->str);
    if (cmp == 0)
        return tree;
    else if (cmp > 0)
        return find_leaf(tree->left, leaf);
    else
        return find_leaf(tree->right, leaf);
}

void apply(tree_t *head, void (*app)(tree_t *, void *), void *arg)
{
    if (!head)
        return;
    // прямой обход (pre-order)
    app(head, arg);
    apply(head->left, app, arg);
    // поперечный (in order)
    apply(head->right, app, arg);
    // обратный (post-order)
}

/// Поиск глубины дерева 
int height_of_tree(tree_t *tree)
{   

    if (tree == NULL)
    {
        return 0;
    }
    else
    { 
        int right, left;    
        if (tree->right != NULL)
        {   
            right = height_of_tree(tree->right);
        }
        else 
        {
            right = -1;
        }
        if (tree->left != NULL)
        {
            left = height_of_tree(tree->left);
        }
        else 
        {
            left = -1;
        }
        int max = left > right ? left : right; 
        return (max + 1);
    }
}

tree_t *find_min(tree_t *tree)
{
    if (!tree)
        return NULL;
    while (tree->left) tree = tree->left;
    return tree;
}


tree_t *remove_leaf(tree_t *tree, tree_t *leaf) // Удаление листа из дерева по имени
{
    if (!tree)
    {
        return tree;
    }
    int cmp = strcmp(tree->str, leaf->str);
    if (cmp > 0)
    {
        tree->left = remove_leaf(tree->left, leaf);
    }
    else if (cmp < 0)
    {
        tree->right = remove_leaf(tree->right, leaf);
    }
    else
    {
        // Узел со значением str найден

        // Узел с одним или без детей
        if (tree->left == NULL)
        {
            tree_t *temp = tree->right;
            free_leaf(tree);
            return temp;
        }
        else if (tree->right == NULL)
        {
            tree_t *temp = tree->left;
            free_leaf(tree);
            return temp;
        }   
        
        // Узел с двумя детьми - найдем минимальное значение в правом поддереве
        tree_t *temp = find_min(tree->right);
        // Скопируем значение минимального узла в текущий узел
        strcpy(tree->str, temp->str);

        // Удалим минимальный узел из правого поддерева
        tree->right = remove_leaf(tree->right, temp);
        // printf("%s\n", tree->right->str);
    }
    return tree;
}


int create_tree_from_input(tree_t **head_n)
{
    ssize_t read;
    size_t count = 0;
    char *buf = NULL;
    tree_t *tree = NULL;
    while ((read = getline(&buf, &count, stdin)) != -1)
    {
        tree_t *leaf = create_leaf(buf);
        if (!leaf)
            break;
        tree = create_tree(tree, leaf);
        free(buf);
        buf = NULL;
        count = 0;
    }
    *head_n = tree;
    return 0;
}


void free_tree(tree_t *head)
{
    if (!head)
        return;
    if (head->left != NULL)
        free_tree(head->left);     
    if (head->right != NULL)
        free_tree(head->right);
    free_leaf(head);
}
