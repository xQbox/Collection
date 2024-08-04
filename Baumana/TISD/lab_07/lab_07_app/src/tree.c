#include "libmy.h"


/// Циклическая инициализация листа дерева
int init_leaf(tree_t *tree_head, tree_t *leaf)
{
    tree_t *tmp = tree_head;
    int cmp = 0;
    while (tmp)
    {
        cmp = strcmp(tmp->word, leaf->word);
        if (cmp > 0)
        {   
            if (tmp->left)
            {
                tmp = tmp->left;
            }
            else 
            {
                tmp->left = leaf;
                break;
            }
        }
        else if (cmp < 0)
        {
            if (tmp->right)
            {
                tmp = tmp->right;
            }
            else 
            {
                tmp->right = leaf;
                break;
            }
        }
        else 
        {
            (tmp->counter)++;
            free(leaf->word);
            free(leaf);
            return false;
        }
    }
    return true;
}

///  Динамическое выделение памяти для листка дерева
tree_t *leaf_create(void)
{
    tree_t *tmp = calloc(1, sizeof(tree_t));
    if (!tmp)
        return NULL;
    tmp->counter = 1;
    tmp->word = NULL;
    tmp->right = NULL;
    tmp->left = NULL;
    // printf("LEAF IN FUNCION\t%s\n", tmp->word);
    return tmp;
}

/// Динамическое выделение памяти для листка дерева и инициализация 
tree_t *leaf_create_with_name(tree_t *leaf)
{
    tree_t *tmp = malloc(sizeof(tree_t));
    if (!tmp)
        return NULL;
    char *tmp_name = malloc(strlen(leaf->word) + 1);
    if (!tmp_name)
        return NULL;
    strcpy(tmp_name, leaf->word);
    // free(tmp->word);
    // free(leaf->word);
    tmp->counter = 1;
    tmp->word = tmp_name;
    tmp->right = NULL;
    tmp->left = NULL;
    return tmp;
}


tree_t *leaf_create_with_name_new(char *word)
{
    tree_t *tmp = malloc(sizeof(tree_t));
    if (!tmp)
    {
        free(word);
        return NULL;
    }
    tmp->word = NULL;
    tmp->counter = 1;
    tmp->word = word;
    tmp->right = NULL;
    tmp->left = NULL;
    return tmp;
}


/// Рекурсивная инициализация листа дерева 
tree_t *insert(tree_t *tree, tree_t *node)
{
    int cmp;
    if (tree == NULL)
        return node;
    cmp = strcmp(node->word, tree->word);
    if (cmp == 0)
    {
        tree->counter++;
        free(node->word);
        free(node);
        // return NULL;
    }
    else if (cmp < 0)
        tree->left = insert(tree->left, node);
    else
        tree->right = insert(tree->right, node);
    return tree;
}


/// Чтение дерева и вывод 
void read_tree(tree_t *tree_head)
{   
    if (tree_head == NULL)
    {
        return;
    }
    else
    {
        if (tree_head->right != NULL)
        {   
            read_tree(tree_head->right);
        }
        if (tree_head->left != NULL)
        {
            read_tree(tree_head->left);
        }
        // print(tree_head);
        
    }
}

/// Прямой поиск слова в дереве
tree_t *find(tree_t *tree, char *name, int *count)
{
    int cmp;
    tree_t *tmp = tree;
    while (tree)
    {
        cmp = strcmp(name, tmp->word); 
        (*count)++;
        if (cmp > 0)
        {
            if (tmp->right)
            {
                tmp = tmp->right;
            }
            else
            {
                // printf("Такого слова нет->%s\n", name);
                break; 
            } 
        }
        else if (cmp < 0)
        {
            if (tmp->left)
            {
                tmp = tmp->left;
            }
            else 
            {
                // printf("Такого слова нет-> %s\n", name);
                break;
            }
        }
        else 
        {
            // printf(" Слово нашлось -> %s\n", tmp->word);
            return tmp;
        }
    }
    return NULL;
}

/// Поиск глубины дерева 
int height_of_tree(tree_t *tree_head)
{   

    if (tree_head == NULL)
    {
        return 0;
    }
    else
    { 
        int right, left;    
        if (tree_head->right != NULL)
        {   
            right = height_of_tree(tree_head->right);
        }
        else 
        {
            right = -1;
        }
        if (tree_head->left != NULL)
        {
            left = height_of_tree(tree_head->left);
        }
        else 
        {
            left = -1;
        }
        int max = left > right ? left : right; 
        return (max + 1);
    }
}

/// Второй алгоритм для поиска глубины дерева 
int HeightOfTree(tree_t * node)
{
    if(node == 0)
        return 0;
    int left, right;
    if (node->left != NULL) {
        left = HeightOfTree(node->left);
    }else 
        left = -1;
    if (node->right != NULL) {
        right = HeightOfTree(node->right);
    }else 
        right = -1;
    int max = left > right ? left : right;
    return max+1;
}

void tree_clean(tree_t *tree_head)
{
    if (tree_head == NULL)
    {
        return;
    } 
    else 
    {
        if (tree_head->left != NULL)
        {
            tree_clean(tree_head->left);
        }
        if (tree_head->right != NULL)
        {
            tree_clean(tree_head->right);
        }
        // printf("%s\n",(tree_head)->word);
        free(tree_head->word);
        free(tree_head);
    }
}

tree_t *find_min(tree_t *tree)
{
    while (tree->left != NULL)
    {
        tree = tree->left;
    }
    return tree;
}


bool tree_is_empty(tree_t *tree)
{
    if ((tree->right == NULL) && (tree->left == NULL))
        return true;
    return false;
}


tree_t *remove_node(tree_t *tree, char *name) // Удаление листа из дерева по имени
{
    if (tree == NULL)
    {
        // free(tree);
        // free(tree->word);
        return tree;
    }
    int cmp = strcmp(tree->word, name);
    if (cmp > 0)
    {
        tree->left = remove_node(tree->left, name);
    }
    else if (cmp < 0)
    {
        tree->right = remove_node(tree->right, name);
    }
    else
    {
        // Узел со значением name найден

        // Узел с одним или без детей
        if (tree->left == NULL)
        {
            tree_t *temp = tree->right;
            free(tree->word);
            free(tree);
            return temp;
        }
        else if (tree->right == NULL)
        {
            tree_t *temp = tree->left;
            free(tree->word);
            free(tree);
            return temp;
        }   
        
        // Узел с двумя детьми - найдем минимальное значение в правом поддереве
        tree_t *temp = find_min(tree->right);
        // Скопируем значение минимального узла в текущий узел
        strcpy(tree->word,temp->word);

        // Удалим минимальный узел из правого поддерева
        tree->right = remove_node(tree->right, temp->word);
        // printf("%s\n", tree->right->word);
    }

    return tree;
}


tree_t **tree_init(size_t size)
{
    tree_t **ptr = (tree_t **) calloc(size, sizeof(tree_t *));
    if (ptr)
    {
        for (size_t i = 0; i < size; ++i)
        {
            ptr[i] = NULL;
        }
        return ptr;
    }
    return NULL;
}

