#include <stdio.h>
#define ALLOCATE_SIZE 10000
void ask_int(int *N);
void input_arr(int *N, int *M);
int find(int *N, int *M, int *ever , int *odd);

int main(void)
{
    int top = 0;
    int ever, odd, pointer; 
    ever = 0;
    odd = 1;
    int A[ALLOCATE_SIZE];
    input_arr(&A[0], &top);
    pointer = find(&A[0], &top, &ever , &odd);
    if (pointer == 0)
    {
        odd = 0;
        printf("%d %d", ever , odd);
    }
    else 
    {
        printf("%d %d", ever , odd);
    }
    return 0;
}


int find(int *N, int *M, int *ever, int *odd)
{   
    int pointer = 0;

    for (int i = 0; i < *M; i ++)
    {
        if ((*(N + i)) % 2 == 0)
        {
            *ever += *(N + i); 
        } 
        else if ((*(N + i)) % 2 == 1)
        {
            *odd *= *(N + i);
            pointer += 1;
        }
    }
    return pointer;
}


void input_arr(int *N, int *M)
{
    while(1)
    {
        int x;
        ask_int(&x);
        *(N + *M) = x;
        if (x == 0 || *M > ALLOCATE_SIZE) break;
        *M += 1;
    }
}


void ask_int(int* N)
{
    
    while(1)
    {
        if ((scanf("%d", N) == 1)) break;
        while (getchar() != '\n');
    }
}