#include "queue.h"
#include <stdio.h>
#include <assert.h>
int main(void)
{
    queue_t q;
    int item;
    int rc;

    q = queue_create();
    if (!q)
        return 1;
    for (item = 0;  !queue_is_full(q) && item < 10; item++)
    {
        rc = queue_push(q, item);
        assert(rc == 0); // для тестового режима в основной программе так делать нельзя 
       
    }
    while (!queue_is_empty(q))
    {
        rc = queue_pop(q, &item);
        assert(rc == 0);
    }
    queue_destroy(q);
    return 0;
}