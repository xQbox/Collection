#include <stdio.h>
#include <math.h>
// int arr(A[], N); посчитать среднне геометрическое полодительных чисел массива 
// void print_arr(char A[], int n);
// int check_number();

int check_number(int n)
{
    int l;
    while(scanf("%d", &l) != 1)
    {
        printf("Wrong input\n");
        printf("Write numbers of Array[%d]: ", n + 1);
        while(getchar() != '\n');
    }
    return l; 
}

void print_arr(int A[], int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("%3d", A[i]);
    }
    printf("\n");
}

    // int arr(A[], N)
    // {
    //     return 
    // }

// int arr(int N ; int A[])
// {
//     while(1)
//     {   
//         printf("Write numbers of Array[%d]: ", i);
//         if(i > 10) break;
//         x = check_number(i);
//         if (x > 0)
//         {
//             A[N] = x;
//             N += 1; 
//         }
//         i += 1;
//     }
//     return N;
// }

int main(void)
{   
    int x, N, i, pointer;
    pointer = 10;
    while (1)
    {
    printf("Write long of Array: ");
    if (scanf("%d", &pointer) == 1 && pointer > 0 && pointer < 11)  break;
    while ( getchar() != '\n');
    }
    int A[10] = {0};
    N = 0; i = 0;
    while(1)
    {
        if(i == pointer) break;
        printf("Write numbers of Array[%d]: ", (i+1));
        x = check_number(i);
        if (x > 0)
        {
            A[N] = x;
            N += 1; 
        }
        i += 1;
    }

    print_arr(A, N);
    int res = 1;
    float new;
    for (int i = 0; i < N; i ++)
    {
        res *= A[i]; 
    }
    new = pow(res, (1. / N));

    printf("Your new -> %f\n", new);
    printf("Your result -> %d\n", res);
    return 0;
}
