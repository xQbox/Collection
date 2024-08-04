#include "libmy.h"
#define ARR_SIZE 20000


int main(void)
{   
    // {
    //     printf("Тестовый случай для функций \n\t1) read_from_file\n\t2) write_in)file\n");
    //     FILE *f;
    //     f = fopen("new.txt", "r+");
    //     tree_t tmp = {0, NULL, NULL, NULL}; 
    //     read_from_file(f, &tmp);
    //     printf("in main -> %s\n", tmp.word);
    //     write_in_file(f, &tmp);
    //     fclose(f);
    //     free(tmp.word);  
    //     printf("\n\n");  
    // }
    // {
        
    //     printf("Программа создает частотный словарь на основе заданного файла\n");
        // tree_t *tree_head = NULL;
        // read_file("text.txt", &tree_head);
        // read_tree(tree_head);
    
        // char name[256];
        // printf("Введите слово для поиска в файле\n>>");
        // fscanf(stdin, "%256s", name);
        // size_t tmp_size = strlen(name);
        // char new_name[tmp_size];
        // strcpy(new_name, name);
        // dump(tree_head);
        
        // tree_t *find_result = NULL;
        // find_result = find(tree_head, name);
        // if (find_result)
        //     printf("%s\n", find_result->word);
        // else 
        // {
        //     printf("Введите место для вставки слова\n");
        //     long new_size = 0;
        //     int pos;
        //     FILE *f = fopen("text.txt", "rb+");
        //     char symbol;
        //     int A[ARR_SIZE];
        //     size_t index;
        //     while ((symbol = getc(f)) != EOF)
        //     {
        //         if (symbol == ' ')
        //         {
        //             A[index] = ftell(f);
        //             index++;
        //         }
        //         new_size ++;
        //     }
        //     fseek(f, 0, SEEK_SET);

        //     printf("Размер файла в байтах %ld\n", new_size);
        //     printf("Введите позицию для записи в файл\n");
        //     if ((fscanf(stdin, "%d", &pos)) != 1)
        //     {
        //         printf("Ошибка ввода\n");
        //         return ERR_NUM;
        //     }
        //     if ((pos > new_size) || (pos < 0))
        //     {
        //         printf("Ошибка позиции\n");
        //         return ERR_NUM;
        //     }
        //     int flag  = 0;
        //     int free_pos = binar_search(A, index, pos, &flag);
        //     pos = A[free_pos];
        //     printf("%d\n", pos);
        //     char M[new_size - pos + 1];
        //     fseek(f, pos, SEEK_SET);
        //     fread(M, sizeof(char), new_size - pos, f);
        //     M[new_size - pos] = '\0';
        //     fseek(f, pos, SEEK_SET);
        //     fwrite(new_name, sizeof(new_name) , 1, f);
        //     char space = ' ';
        //     fwrite(&space, sizeof(space), 1, f);
        //     fwrite(M, sizeof(M) - 1, 1, f);
        //     fclose(f);
    //     }
    //     printf("Дерево имеет вид\n");
    //     clock_t a = clock();
    //     if (!(find_in_file("text.txt", new_name)))
    //     {
    //         double time = (double) (clock() - a) / CLOCKS_PER_SEC;
    //         printf("\nВремя поиска в файле-> %lf\n", time); 
    //     }

    //     tree_t leaf = {1, new_name, NULL, NULL};
    //     tree_head = insert(tree_head, &leaf);
    //     find_result = NULL;
    //     clock_t time_start = clock();
    //     find_result = find(tree_head, name);
    //     double time_end = (double) (clock() - time_start) / CLOCKS_PER_SEC;
    //     printf("\nВремя поиска в дереве-> %lf\n", time_end);
    //     printf("\n\n");
    // }

    printf("Программа создает частотный словарь на основе файла\n");
    printf("Открыт файл text.txt");
    tree_t *tree_head = NULL;
    read_file("text.txt", &tree_head);;
    read_tree(tree_head);
    char *filename = "text.txt";
    int choice = 0;
    char tmp;
    char free_space[2];
    while (choice != EXIT)
    {
        menu_print();
        choice = 0;
        if ((fscanf(stdin, " %c", &tmp)) == 1)
        {
            scanf("%*[^\n]");
            
            fgets(free_space, sizeof(free_space), stdin);
            if (tmp > '0' && tmp < '9')
            {
                sscanf(&tmp, "%d", &choice);
                choice--;
                choose(choice, &tree_head, filename);
            }
            else 
            {
                continue;
            }
        }
    }
    return ERR_OK;
}
