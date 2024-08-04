#include <stdio.h>
/*Лабораторная работа номер 1 Задача 5 вариант 4 . Выполнил ст гр ИУ7-21БВ Родинков Алексей */
int check_nmb(void) 
{   
    int c;    
    while (scanf("%f", &c) != 1 )
    {
        printf("Wrong input\n");
        while(getchar() != '\n');   
    }
    return c;
} 
void print_number_factors(int x)
{
   printf("Number factors: ");
   int divisor = 2;
   while(x != 1)
   {
       if (x%divisor == 0)
       {
           printf("%d ", divisor);
           x /= divisor;
       }
       else
           divisor += 1;
   }
   printf("\n");
}

int main(int argc, char* argv[])
{
   int x;
   printf("Enter number to factorize: ");
   x = check_nmb();
   print_number_factors(x);
   return 0;
}
