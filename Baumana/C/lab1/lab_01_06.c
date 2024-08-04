/*Лабораторная работа номер 1 Задача 6 вариант 0 . Выполнил ст гр ИУ7-21БВ Родинков Алексей */
#include <stdio.h>
#include <math.h>
#define MIN(a,b) (((a)<(b)?(a):(b)))
#define MAX(a,b) (((a)>(b)?(a):(b)))

int check_nmb(void) 
{   
    float c;    
    while (scanf("%f", &c) != 1 || c < 0)
    {
        printf("Wrong input\n");
        while(getchar() != '\n');   
    }
    return c;
} 

int main()
{
    float x0, y0, x1, y1, x2, y2, a, b, c;
    printf("Write first point's values (x0): ");
    x0 = check_nmb();
    printf("\nWrite first point's values (y0): ");
    y0 = check_nmb();
    printf("\nWrite second point's values (x1): ");
    x1 = check_nmb();
    printf("\nWrite second point's values (y1): ");
    y1 = check_nmb();
    printf("\nWrite random point's values (x2): ");
    x2 = check_nmb();    
    printf("\nWrite second point's values (y2): ");
    y2 = check_nmb(); 
    a = sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
    b = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    c = sqrt((x0 - x2) * (x0 - x2) + (y0 - y2) * (y0 - y2));
    if ((a - b == 0) || (c - b == 0) || (a - c == 0))
        printf("\nError\n");
    else 
    {
        float best = MAX(MAX(a, b), c);
        if (best == a)
        {
            if (((powf(best, 2)) - (b * b + c * c)) > 0)
                printf("\n2 - tupougolnii");
            else if (((powf(best, 2)) - (b * b + c * c)) == 0)
                printf("\n1 - prymougolnii");
            else if (((powf(best, 2)) - (b * b + c * c)) < 0)
                printf("\n0 - ostro");
        }  
        else if (best == b)
        {
                    
            if (((powf(best, 2)) - (a * a + c * c)) > 0)
                printf("\n2 - tupougolnii\n");
            else if (((powf(best, 2)) - (a * a + c * c)) == 0)
                printf("\n1 - prymougolnii\n");
            else if (((powf(best, 2)) - (a * a + c * c)) < 0)
                printf("\n0 - ostro\n");
        }
        else if (best == c)
        {

            if (((powf(best, 2)) - (b * b + a * a)) > 0)
            {
                printf("\n2 - tupougolnii\n");
            }
            else if (((powf(best, 2)) - (b * b + a * a)) == 0)
            {
                printf("\n1 - prymougolnii\n");
            }
            else if (((powf(best, 2)) - (b * b + a * a)) < 0)
            {
                printf("\n0 - ostro\n");
            }
        }
    }
}
