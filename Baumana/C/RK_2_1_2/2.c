#include <stdio.h>
void ask_int(int* N);
void divisor(int *N, int M);
int divisor1(int N);
int check(int *N, int size, int res, int place , int nmb);
int find_arr(int *N , int size);



int main(void)
{
    int b;
    ask_int(&b);
    const int size = divisor1(b);
    int A[size];
    printf("\nsize %d\n", size);
    divisor(&A[0], b);
    for (int i =0 ; i < size; i++)
    {
        printf("%3d", A[i]);
    }
    // sort(&A[0], size);
    // new_arr(&A[0], size, &M[0]);
    
    printf("\n\n\n");
    int L = find_arr(&A[0], size);
    for (int i = 0 ; i < size ; i++)
    {
        printf("%3d", A[i]);
    }
    printf("\n%d\n", L);
    return 0;
}


int check(int *N, int size, int res, int place, int point)
{ 
    for (int i = place + 1; i < size - res; i++)
    {
        if (*(N + i) == point)
        {
            printf("This is point ->%3d", *(N + i));
            int q = i;
            while (q < size - res -1)
            {
                int temp = *(N + q + 1);
                *(N + q + 1)  = *(N + q);
                *(N + q) = temp;
                q += 1;
            }
          res += 1;
        }
    }
    return res;
}



void divisor(int *N, int M)
{
    int res = 0;
    int i = 0;
    while (M != 0)
    {
        res = M % 10;
        M /= 10;
        *(N + i) = res;
        i += 1;
    }
}



int find_arr(int *N , int size)
{
    int res = 0;
    for (int i = 0; i < size; i++)
    {   
        res = check(N, size, res, i, *(N + i));
    }
    res = size - res;
    return res;
}


int divisor1(int N)
{
    int res = 0;
    while (N != 0)
    {
        N /= 10;
        res += 1;
    }
    
    return res;
}


void ask_int(int* N)
{
    
    while(1)
    {
        if ((scanf("%d", N) == 1)) break;
        while (getchar() != '\n');
    }
}


