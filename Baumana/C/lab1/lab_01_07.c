/*Лабораторная работа номер 1 Задача 7 вариант 4 . Выполнил ст гр ИУ7-21БВ Родинков Алексей */
#include <stdio.h>
#include <math.h>

int check_nmb(void) 
{   
    float c;    
    while (scanf("%f", &c) != 1)
    {
        printf("Wrong input\n");
        while(getchar() != '\n');   
    }
    return c;
} 

int current(int n, float x)
{
  float sum;
  sum = (powf(-1, n) * ((n + 1)*(n + 2) * powf(x, n))) / 2;
  return sum;
}
int main()
{
   float e, x;
   double func, sum, delta , sigma;
   int n = 1;
   printf("Write value of x between (-1 < x < 1): ");
   x = check_nmb();
   while ((x < -1.) && (x > 1.)) 
   {
    x = 0;
    x = check_nmb();
   }
   printf("Write value of e between (0 < e < 1): ");
   e = check_nmb();
   while ( (e < 0) && (e > 1)) 
   {
    e = 0;
    e = check_nmb();
   }
   sum = 1;
   func = 1 / powf((1 + x), 3);
   while (e < fabs(sum))
   {
       sum = (powf(-1, n) * ((n + 1)*(n + 2) * powf(x, n))) / 2;
       printf("%d) ", n);
       printf("Sum %f\n", sum);
       n ++;
   }
   printf("Your approximately solution is %f\n", sum);
   printf("Your equal solution is %f\n", func);
   delta = fabs(func - sum);
   sigma = fabs(func - sum) / fabs(func);
   printf("Your delta is -> %f\n", delta);
   printf("Your sigma is -> %f\n", sigma);
}
