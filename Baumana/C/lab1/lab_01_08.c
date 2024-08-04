// Лабораторная работа номер 1 Задача 8 вариант 3 . Выполнил ст гр ИУ7-21БВ Родинков Алексей
#include <stdio.h>
#define N 32
int check_nmb(void) 
{   
    float c;    
    while (scanf("%f", &c) != 1 || c < 1)
    {
        printf("Wrong input\n");
        while(getchar() != '\n');   
    }
    return c;
} 

int main()
{
   int put, i, tmp;
   printf("Write your number: ");
   put = check_nmb();
   i = 0;
   int A[N] = {0};
   while (put / 2 != 0)
   {
       A[i] = put % 2;
       i ++;
       put /= 2;
   }
   if (put == 1)
       A[i] = 1;
   for (int i = 0; i < N; i ++)
       printf(" %d ", A[i]);
   printf("\n");
   for (int i = 0; i <  N / 2 ; ++i)
   {
       tmp = A[i];
       A[i] = A[N - 1 - i];
       A[N - 1 - i] = tmp;
   }
   for (int i = 0; i < N; i ++)
       printf(" %d ", A[i]);
   printf("\n");
   for (int i = 0; i < N; i ++)
   {
       if (i % 2 == 0)
       {
           tmp = A[i];
           A[i] = A[i+1];
           A[i+1] = tmp;
       }
   }
   printf("\n");
   for (int i = 0; i < N; i ++)
       printf(" %d ", A[i]);
   printf("\n");
   for (int i = 0; i < N ; ++i)
   {
       if (A[i] == 1)
       {
           for(int j = i; j < N; ++j)
               printf(" %d ", A[j]);
       break;
       }
   }
}