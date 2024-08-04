#include <stdio.h>
#include <math.h>
#define MIN(A, B) (((A) < (B)) ? (A) : (B))

int ask_int()
{   int res;
    while (1)
    {   
        printf("Write size of Array: ");
        if (scanf("%d", &res) == 1 && res > 0 && res < 11) break;
        while(getchar() != '\n');   
    }   
    return res;
}


int init_mas(int *p, int top)
{   
    int res = 0;
    int b = 1;
    printf("\n%d\n", *p + top);
    for(int *i  = p; i < (int *) p + top; i++)
    {      
        int r; 

        printf("Write some numbers of Array[%d]-> ", b);
        r = scanf("%d", i);
        res += 1;
        if (r == 0) 
        {
            res -= 1;
            break;
        }
        b += 1;
    }
    return res;
}


int check_sort(int *p, int top)
{
     int plus, minus, total;
    plus = minus = 0;
    // for (int *i = p; i < (int *)p + 10; i++)
    for(int *i = p; i < (int *)p + top; i++)
    {
        if (*i > 0)
            plus += 1;
        else if (*i < 0)
            minus += 1; 
    }
    total = MIN(minus, plus);
    return total;
}


int insert_sort(int *p, int total, int top)
{
    int i, n, res, flag, minus, plus;
    i = n = res = flag = minus = plus = 0;
    while (flag != (total))
    {
        while (1)
        {
            if (*(p + i) > 0)
            {
                plus = *(p + i);
                printf("THIS IS YOUR PLUS -> %d\n", plus);
                break;
            } 
            i += 1;
        }
        while (1)
        {
            if (*(p + top - n) < 0) 
            {
                minus = *(p + top - n);
                printf("THIS IS YOUR MINUS -> %d\n", minus);
                break;
            }
            n += 1;
        }
        i += 1;
        n += 1;
        res +=  (plus * minus);
        flag += 1;
    }
    return res;
}


void print_arr(int *p, int top)
{
    int q = 0;
    for(int *i = p; i < (int *)p + top; i++)
    {
        printf("%3d", *i);
        q += 1;
        if (q % 3 == 0) 
            printf("\n");
    }
    printf("\n");
}


int main(void)
{

    int A[10] = {0};
    int top, total, res;
    int *p = A;
    res = ask_int();
    top = init_mas(p, res);
    print_arr(p, top);
    total = check_sort(p, top);
    if (total == 0)
    {
        printf("Cant count\n");
        return 1;
    }
    else if (total > 0)
    {
        int res;
        res = insert_sort(p, total, top);
        printf("This is your Result -> %d", res);
        if (top == 10) 
            return 100;
        else
            return 0;
    }
}