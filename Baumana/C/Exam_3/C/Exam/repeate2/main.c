
#include "node.h"


int main(void)
{
    int rc = 1;
    node_t *head = NULL;
    while((rc = input_line(&head)) != 0);
    if (!head)
        return 1;
    // print_list(head);
    node_t *new_list = exercise(&head);
    new_list = add(new_list, head);
    print_list(new_list);
    return 0;
}