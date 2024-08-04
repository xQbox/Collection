// #include "libmy.h"
#include <stdio.h>
#include <stdlib.h>
#define ECHO(s) {gets(s); puts(s);}


int main(void)
// {
//     char *choose = input_line(1);
//     int rc = 0;
//     if ((strcmp(choose, "tree\n")) == 0)
//     {
//         tree_t *head  = NULL;
//         rc = create_tree_from_input(&head);
//         int a = 0;
//         apply(head, print_leaf, &a);
//         free_tree(head);
//     }
//     else if ((strcmp(choose, "node\n")) == 0)
//     {
//         node_t *head = NULL;
//         rc = create_list(&head);
//         print_list(head);
//         node_t *res = find_node(head, comp_node);
//         print_node(res);
//         free_list(head);
//     }
//     else if (((strcmp(choose, "hash\n")) == 0))
//     {
//         hash_t *head = NULL;
//         rc = create_hash_table(&head);
//         print_hash(head);
//     }
//     else if (((strcmp(choose, "arr\n")) == 0))
//     {

//     }
//     else if ((strcmp(choose, "stack\n")) == 0)
//     {

//     }
//     else if ((strcmp(choose, "queue\n")) == 0)
//     {

//     }
//     else if (((strcmp(choose, "heap\n")) == 0))
//     {

//     }
//     else 
//     {
//         printf("Undefined name of ADT\n");
//         rc = 2;
//     }
//     free(choose);
//     return rc;
// }
// {
//     char x = 4;
//     printf("%ld %ld %ld " , sizeof(char), sizeof(int), sizeof(double));
//     printf("%d \n", 0 / 5);
//     printf("%ld\n", sizeof(x - 1) / sizeof(x) + 1);
//     printf("%ld\n", sizeof(x) / sizeof(x) + 1);
// }
{
    char *s = malloc(100);
    int echo_flag = 0;
    if (echo_flag)
    {
        ECHO(s);
    }
    else 
        ECHO(s);
    printf("\n%s\n", s);
    free(s);
}