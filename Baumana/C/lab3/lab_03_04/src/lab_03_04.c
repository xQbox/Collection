#include <stdio.h>
#include <math.h>
void ask_int(int *N);
void ask_matrix(int *N, int *M);
void input_matrix(int *N, int row, int column);
void print_array(int *N, int sum);



int main(void)
{
    int row, column;
    ask_matrix(&row, &column);
    int A[row][column];
    input_matrix(&A[0][0], row, column);
    print_array(&A[0][0], row * column);
    return 0;
}


void ask_matrix(int *N, int *M)
{
    while(1)
    {
        printf("Write quantity rows : ");
        ask_int(N);
        if (*N > 0 && *N < 11) break;
    } while(1)
    {
        printf("Write quantity columns : ");
        ask_int(M);
        if ( *M > 0 && *M < 11) break;
    }
}


void ask_int(int *N)
{
    while(1)
    {
        if (scanf("%d", N) == 1) break;
        while(getchar() != '\n');
    }
}


void input_matrix(int *N, int row, int column)
{
    for(int i = 0; i < row; i++)
    {
        for(int k = 0; k < column; k++)
        {
            int b;
            ask_int(&b);
            *(N + i * column + k)  = b;
        }
    }
}


void print_array(int *N, int sum)
{
    printf("Direct access to memory \n\n");
    for(int i = 0; i < sum; i++)
    {
        printf("%3d", *(N + i));
    }
    printf("\n");
}

