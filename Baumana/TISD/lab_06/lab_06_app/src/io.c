#include "libmy.h"


int choose(int choice, tree_t **tree_head, char *filename)
{
    if (choice == PRINTTREE)
    {
        export_tree_to_dot("DEREVO", *tree_head);
        dump(*tree_head);
    }
    else if (choice == ADDWORDINTREE)
    {
        printf("Введите слово для добавления в дерево\n>>");
        char name[256];
        
        fgets(name, sizeof(name), stdin);
        // printf("%s\n", name); 
        if (name[strlen(name) - 1] == '\n')
        {
            name[strlen(name) - 1] = '\0';
        }
        tree_t tmp = {1, name, NULL, NULL};
        tree_t *leaf = leaf_create_with_name(&tmp);
        init_leaf(*tree_head, leaf);
    }   
    else if (choice == ADDWORDINFILE)
    {
        char name[256];
        printf("Введите слово для вставки в файл`\n>>");
        fscanf(stdin, "%256s", name);
        scanf("%*[^\n]");
        size_t tmp_size = strlen(name);
        char new_name[tmp_size];
        strcpy(new_name, name);
        printf("Введите место для вставки слова\n");
            long new_size = 0;
            int pos;
            FILE *f = fopen("text.txt", "rb+");
            char symbol;
            int A[ARR_SIZE];
            size_t index;
            while ((symbol = getc(f)) != EOF)
            {
                if (symbol == ' ')
                {
                    A[index] = ftell(f);
                    index++;
                }
                new_size ++;
            }
            fseek(f, 0, SEEK_SET);

            printf("Размер файла в байтах %ld\n", new_size);
            printf("Введите позицию для записи в файл\n");
            if ((fscanf(stdin, "%d", &pos)) != 1)
            {
                printf("Ошибка ввода\n");
                return ERR_NUM;
            }
            if ((pos > new_size) || (pos < 0))
            {
                printf("Ошибка позиции\n");
                return ERR_NUM;
            }
            scanf("%*[^\n]");
            int flag  = 0;
            int free_pos = binar_search(A, index, pos, &flag);
            pos = A[free_pos];
            char M[new_size - pos + 1];
            fseek(f, pos, SEEK_SET);
            fread(M, sizeof(char), new_size - pos, f);
            M[new_size - pos] = '\0';
            fseek(f, pos, SEEK_SET);
            fwrite(new_name, sizeof(new_name) , 1, f);
            char space = ' ';
            fwrite(&space, sizeof(space), 1, f);
            fwrite(M, sizeof(M) - 1, 1, f);
            fclose(f);
            char tmp[2];
            fgets(tmp, sizeof(char), stdin);
    }
    else if (choice == OPENNEWFILE)
    {
        printf("Введите название нового файла для открытия и инициализации\n>>");
        char tmp[256];
        fgets(tmp, sizeof(tmp), stdin);
        if (tmp[strlen(tmp) - 1] == '\n')
        {
            tmp[strlen(tmp) - 1] = '\0';
        }
        char file[strlen(tmp) + 1];
        strcpy(file, tmp);
        printf("%s\n", file);
        printf("%d\n", file_check(file));
        if (!file_check(file))
        {
            tree_clean(*tree_head);
            *tree_head = NULL;
            read_file(file, tree_head);
            printf("%s %d\n", (*tree_head)->word, (*tree_head)->counter);
            // free(filename);
            filename = file;
        }
        else 
        {
            printf("Ошибка при работе с файлом \n");
        }
    }
    else if (choice == FIND)
    {
        char name[256];
        printf("Введите слово для поиска в файле\n>>");
        fscanf(stdin, "%256s", name);
        scanf("%*[^\n]");
        size_t tmp_size = strlen(name);
        char new_name[tmp_size];
        strcpy(new_name, name);
        tree_t *find_result = NULL;
        clock_t a = clock();
        // printf("%p\n" (void *) *tree_head);
        find_result = find(*tree_head, name);
        // printf("%p\n" (void *) *tree_head);
        double fin_time = (double) (clock() - a) / CLOCKS_PER_SEC; 
        if (find_result)
        {
            clock_t b = clock();
            find_in_file(filename, new_name);
            double time_end = (double) (clock() - b) / CLOCKS_PER_SEC; 
            printf("Поиск :\nв дереве %lf\nв файле %lf\n", fin_time, time_end);
        }
        else 
        {
            printf("Такого слова нет: %s\n", new_name);
        }
    }
    else if (choice == DELETEINTREE)
    {
        char name[256];
        printf("Введите слово для удаления\n");
        fscanf(stdin, "%256s", name);
        size_t tmp_size = strlen(name);
        char new_name[tmp_size];
        strcpy(new_name, name);
        tree_t *result = find(*tree_head, new_name);
        if (result)
        {
            clock_t a = clock();
            *tree_head = remove_node(*tree_head, new_name);
            double end = (double) (clock() - a) / CLOCKS_PER_SEC;
            printf("Время на удаление : %lf\n", end);
        }
        else 
        {
            printf("слова нет в дереве\n");
        }
    }
    else if (choice == DELETEINFILE)
    {
        FILE *f = fopen(filename, "r"); 
        char name[256];
        int rc ;
        printf("Введите слово для удаления\n");
        fscanf(stdin, "%256s", name);
        size_t tmp_size = strlen(name);
        char new_name[tmp_size];
        strcpy(new_name, name);
        rc = find_in_file(filename, new_name);
        char name_new[256];
        long pos_after_word, pos_before_word;
        if (!rc)
        {
            while ((fscanf(f, "%256s", name_new)) == 1)
            {
                if (strcmp(new_name, name_new) == 0)
                {
                    pos_after_word = ftell(f);
                    // printf("pos -> %ld", pos_after_word);
                    pos_before_word = pos_after_word - strlen(name_new) ;
                    // printf("pos -> %ld", pos_before_word);
                    break;
                }   
            }
            char FILE_END[20000];
            int index = 0;
            char k;
            while ((k = getc(f)) != EOF)
            {
                FILE_END[index] = k;
                index++;
            }
            fseek(f, 0, SEEK_SET);
            char FILE_START[20000];
            int i = 0;
            clock_t a = clock();
            while (i < pos_before_word)
            {
                FILE_START[i] = getc(f);
                i++;
            }
            fclose(f);
            f = fopen(filename, "w");
            int p = 0;
            while (p < i)
            {
                fprintf(f, "%c", FILE_START[p]);
                p++;
            }
            p = 0;
            while (p < index)
            {
                fprintf(f, "%c", FILE_END[p]);
                p++;
            }
            double end = (double) (clock() - a) / CLOCKS_PER_SEC;
            printf("Время на удаление : %lf\n", end);
            fclose(f);
        }
        else 
        {
            printf("слова нет в файле\n");
        }
    }
    return ERR_OK;
}

void print(tree_t *head)
{
    fprintf(stdout, "\"%s\" встречено %d - раз\n", head->word, head->counter);
}


void menu_print()
{
    // system("clear");
    printf("\nОсновное меню программы\n\t");
    printf("1 - Вывод дерева\n\t");
    printf("2 - Добавление слова в дерево\n\t");
    printf("3 - Добавление слова в файл\n\t");
    printf("4 - Открыть другой файл\n\t");
    printf("5 - Поискa\n\t");
    printf("6 - Удаление в дереве\n\t");
    printf("7 - Удаление в файле\n\t");
    printf("8 - Завершение работы программы\n");
}



void dump(tree_t *node)
{
    dump0(node, "", 1, 1);
}

void dump0(tree_t *node, const char* prefix, int root, int last)
{
    if (node != NULL) {
        printf("%s", prefix);
        if (root) {
            printf("└── ");
        } else if (last) {
            printf("├── ");
        } else {
            printf("├── ");
        }
        printf("%s %d\n", node->word, node->counter);

        const char* newPrefix = last ? "    " : "│   ";

        if (node->left != NULL || node->right != NULL) {
            if (node->left != NULL) {
                char* leftPrefix = (char*)malloc(strlen(prefix) + strlen(newPrefix) + 1);
                strcpy(leftPrefix, prefix);
                strcat(leftPrefix, newPrefix);
                dump0(node->left, leftPrefix, 0, node->right == NULL);
                free(leftPrefix);
            }
            if (node->right != NULL) {
                char* rightPrefix = (char*)malloc(strlen(prefix) + strlen(newPrefix) + 1);
                strcpy(rightPrefix, prefix);
                strcat(rightPrefix, newPrefix);
                dump0(node->right, rightPrefix, 0, 1);
                free(rightPrefix);
            }
        }
    }
}

void PrintTree (tree_t *pNode, int n) 
{ 
    if (pNode->left) PrintTree(pNode->left, n+1); 

    for (int i = 0; i < n; i++) printf(" "); 
    printf("%s %d\n", pNode->word, pNode->counter); 

    if (pNode->right) PrintTree(pNode->right, n+1); 
}


void printTree_new(tree_t *root, int level)
{
    if (root == NULL) {
        return;
    }
    printTree_new(root->right, level + 1);
    for (int i = 0; i < level; i++) {
        printf("   ");
    }
    printf("\"%s\" раз - %d\n", root->word, root->counter);
    printTree_new(root->left, level + 1);
}



void print_node_as_dot(tree_t *node, void *param)
{
    FILE *f = param;

    if (node->left)
        fprintf(f, "%s_%d -> %s_%d;\n", node->word, node->counter, node->left->word, node->left->counter);

    if (node->right)
        fprintf(f, "%s_%d -> %s_%d;\n", node->word, node->counter, node->right->word, node->right->counter);
}

void export_tree_to_dot(const char *tree_name, tree_t *tree)
{

    FILE *f = fopen("tree.dot", "w");
    if (!f)
        return;

    fprintf(f, "digraph %s {\n", tree_name);
    fprintf(f, "node [shape=circle, style=filled, color=black, fontcolor=white];\n");

    

    traverse_tree_pre(tree, print_node_as_dot, f);

    fprintf(f, "}\n");

    fclose(f);

    char command[256];
    snprintf(command, sizeof(command), "dot -Tpng tree.dot -o %s", "tree.png");

    // Execute Graphviz command
    int result = system(command);

    if (result != 0)
    {
        fprintf(stderr, "Error executing Graphviz command.\n");
    }
    else
    {
        printf("Tree visualization saved as tree.png\n");
    }
    system("echo 990436 | sudo -S eog tree.png");
}

void traverse_tree_pre(tree_t *tree, void (*f)(tree_t *, void *), void *arg)
{
    if (tree == NULL)
        return;

    f(tree, arg);
    traverse_tree_pre(tree->left, f, arg);
    traverse_tree_pre(tree->right, f, arg);
}
// void print_line(tree_t *leaf, int all_size, int start)
// {
//     int mid = all_size / 2;
//     for (int i = start; i < all_size; ++i)
//     {
//         printf("-");
//         if (i == mid)
//         {
//             printf("%s %d", leaf->word, leaf->counter);
//         }
//     }
// }                                                                                                                                     

// void print_tree(tree_t *tree_head, int all_size, int start)
// {
//     if (!tree_head)
//     {
//         return;
//     }
//     else 
//     {

//     }
// }



//  int mid = all_size / 2;
//         printf("|");
//         int counter = 0;
//         for (int i = start; i < all_size; ++i)
//         {
//             if (((i + ((int)strlen(tree_head->word) / 2)) + mid / 2) == mid)
//             {
//                 counter++;
//             }
//             if ((i + ((int)strlen(tree_head->word) / 2)) == mid)
//             {
//                 printf("%s %d", tree_head->word, tree_head->counter);
//                 i += (strlen(tree_head->word) + 3);
//                 counter = 1;
//             }
//             if (counter > 0)
//             {
//                 printf("-");
//                 counter++;
//                 if (counter > mid / 2)
//                     counter = 0;
//             }
//             else 
//             {
//                 printf(" ");
//             }
//         }
//         printf("|\n");
//         n--;
//         printf("|");
//         for (int i = start; i < all_size; ++i)
//         {
//             if (((i + ((int)strlen(tree_head->word) / 2)) + mid / 2) == mid)
//             {
//                 printf("|");
//             }
//             else if (i == ((int) (mid + strlen(tree_head->word) / 2) + (mid / 2) - 1 ))
//             {
//                 printf("|");
//             }
//             else 
//             {
//                 printf(" ");
//             }
//         }
//         printf("|\n");
        