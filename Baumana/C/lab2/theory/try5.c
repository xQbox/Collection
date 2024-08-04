#include <stdio.h>
#define MIN(A, B) (((A) < (B)) ? (A) : (B))
int insert_sort(int *p)
{
    printf("HElllooo");
    int plus, minus, total;
    plus = minus = 0;
    // int cur = 0;
    for (int *i = p; i < (int *)p + 10; i++)
    {
        printf("My number %d\n", *i );
        if (*i > 0)
            plus += 1;
        else if (*i < 0)
            minus += 1; 
    }
    total = MIN(minus, plus);
    int i, n, res, flag;
    i = n = res = flag = minus = plus = 0;
    printf("%d\n" , total);
    while (flag != (total))
    {
        while (1)
        {
            if (*p > 0)
            {
                plus = *p;
                printf("THIS IS YOUR PLUS -> %d\n", *p);
                break;
            } 
            i += 1;
        }
        while (1)
        {
            if (*(p + 9 - n) < 0) 
            {
                minus = *(p + 9 - n);
                printf("THIS IS YOUR MINUS -> %d\n", minus);
                break;
            }
             n += 1;
        }
        i += 1;
        n += 1;
        res +=  (plus * minus);
        printf("This is your RESULT -> %d\n", res);
        flag += 1;
    }
    return res;
}

int main(void)
{
    char a[1]; 
    int A[10] = {100, 1, 3, 1, -1, -1, 1, a};
    int *p = A;
    int *q = A+9;
    insert_sort(p);
    printf("%d\n" ,*q);
    return 0;
    // int b;
    // b = insert_sort(p);
    // printf("%d\n" , b);
}