#include <stdio.h>
#include <math.h>
#define MAXIMUM_SIZE 10

void input_array(int *p, int column_top, int row_top);
void print_array2(int *p, int column_top, int row_top);
int find_array(int *p, int column_top, int row_top, int M[]);
void print_array(int *parr, int place);

int  main (void)
{   
    int A[][10] = {0};
    // int parr = *(int *)A + sizeof(int); 
    int row_top, column_top, place;
    // Запрос на количество строк в массиве
    while (1)
    {
    int chk = 0;
    printf("Write rows of Array (0; 11) : ");
    chk = scanf("%d", &row_top);
    if (chk != 0)
    {
        if ((row_top < 11) && (0 < row_top)) break;    
    }   
    while(getchar() != '\n');
    }
    //
    
    // Запрос на количество столбцов в массиве
    while(1)
    {
    int check = 0;
    printf("Write columns of Array (0; 11) : ");
    check = scanf("%d", &column_top);
    if (check != 0)
    {
        if ((column_top < 11) && (0 < column_top)) break;
    }
    while(getchar() != '\n');
    }
    int p = *((int *)A + sizeof(int) * 6 + 7); 
    //
    input_array(&p, column_top, row_top);
    printf("\n\n"); 
    print_array2(&p , column_top, row_top);
    int M[10] = {0};
    int parr = *M;
    place = find_array(&p, column_top, row_top, M);
    printf("\n\n");
    printf("THIS IS YOUR PLACE -> %d\n", place);
    print_array(&parr, place);
    printf("\n\n");
    return 0;
} 


void input_array(int *p, int column_top, int row_top)
{
    int point = 0;
    for(int *i = p; i < (int *)p + column_top * row_top; i ++)
    {   

        printf("Write number of array [%d]-> ", (point + 1));
        scanf("%d", i);   
        point += 1;
        if (point % column_top == 0)
            point = 0;
    }
    point = 0;
    for (int *i = p; i < (int *) p + column_top * row_top; i ++)
    {
        printf("%3d", *i);
        point += 1;
        if (point % column_top == 0)
        {
            printf("\n");
            point = 0;
        }
    }
}

void print_array2(int *p, int column_top, int row_top)
{   
    int point = 0;
    for (int *i = p; i < (int *) p + column_top * row_top; i++)
    {   
        printf("%3d", *i);
        point += 1;
        if (point % column_top == 0) 
        {
            printf("\n");
            point = 0;
        } 
    }
}

int find_array(int *p, int column_top, int row_top, int M[])
{
    int flag = 1; 
    int count, place;
    place = 0;
    count = 0;
    for (int *i = p; i < (int *)p + column_top * row_top; i++)
    {
        if (*(i + column_top / 2) == *i)
            count += 1;
        
        if ((*(i + column_top / 2)) == *i)
        {   
            if (count == column_top / 2)
            {
                M[place] = 1;
                place += 1;
            }
            else if (count != column_top / 2)
            {
                M[place] = 0; 
                place += 1;
            }
            *i = column_top * flag;
            flag += 1;
            count = 0;
        }
    }
    return place;
}

void print_array(int *parr, int place)
{
    for (int * i = parr; i < (int *) parr + place; i ++)
    {
        printf("%3d", *i);
    }
}

// void print_array(int *p, int top, int N)
// {
//     for (int *i = p; i < (int *)p + top; i++)
//     {
//         printf("%3d", *i);
//         if (int *i % N == 0) 
//             printf("\n");
//     }
//     printf("\n");
// }




// int main(void)
// {
//     int A[4][4] = {{0}};
//     int *p = *A;
//     int M[4] = {-1, -1, -1, -1};
//     for(int i = 0; i < 4; i++)
//     {
//         for (int k = 0; k < 4; k++)
//         {
//             scanf("%d", &A[i][k]);
//         }
//     }
//     for (int i = 0; i < 4 ; i++)
//     {
//         int count = 0;
//         for (int k = 0; k < 2; k ++)
//         {
//             if (A[i][k] == A[i][k+2])
//             {
//                 printf("\n K -> %d; ", A[i][k]);
//                 printf("K + 2 ->   %d\n", A[i][k+2]);
//                 printf("\nITS IS YOUR K --- %d \n", k);
//                 count +=1; 
//                 printf("\nCOUNT ---- %d\n", count);
//             }
//         }
//         if (count == 2)
//         {
//             M[i] = 1;
//         }
//         else if (count != 2)
//         {
//             M[i] = 0;
//         }
//     }
//     for (int i = 0; i < 4; i++)
//     {
//         printf("%3d", M[i]);
//     }
//     printf("\n");
//     printf("A -> %d" , *(p + 13));
//     return 0;
// }