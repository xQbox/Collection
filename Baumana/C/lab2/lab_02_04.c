#include <stdio.h>
#include <math.h>
#define L 10
int ask_int()
{
    int b;
    while (1)
    {   
        printf("Write size of Array: ");
        if (scanf("%d", &b) == 1 && b > 0 && b < 11) break;
        while(getchar() != '\n');
    }
    return b;
}
int init_mas(int* p, int pointer)
{
    int top = 0;
    for(int i  = 0; i < pointer; i++)
    {      
        int r; 
        printf("Write some numbers of Array[%d]-> ", i+1);
        r = scanf("%d", p + i);
        if (r == 0) break;
        top += 1;
    }
    return top;
}
void insert_sort(int A[], int N)
{
    for (int i = 1; i < N; i ++)
    {
        int k = i;
        while (k > 0 && A[k - 1] > A[k])
        {

            int tmp = A[k - 1];
            A[k - 1] = A[k];
            A[k] = tmp;
            k -= 1;
        }
    }
}

void print_arr(int A[], int N)
{
    for(int i = 0; i < N; i++)
    {
        printf("%3d", A[i]);
        if (i % 3 == 0) 
            printf("\n");
    }
    printf("\n");
}
int main(void)
{

    int A[10] = {0};
    int top, res;
    int *parr = A;
    res = ask_int();
    top = init_mas(parr, res);
    insert_sort(A, top);
    print_arr(A, top);
    if (top == 10) 
        return 100;
    else
        return 0;
}