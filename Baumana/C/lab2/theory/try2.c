#include <stdio.h>
#include <math.h>
int recheck(int n)
{
    int res, final, num, flag, itog;
    num = n;
    itog = n;
    flag = 0;
    while (n % 10 != 0)
    {
        while (num % 10 != 0)
        {
            num /= 10;
            flag += 1;
            printf("this is your FLAG-> %d\n", flag);
        }
        res = n % 10;
        printf("this is your RESULT-> %d\n", res);
        final += pow(res, flag);
        n /= 10;
        printf("this is your POW-> %d\n", final);
    }
    
    printf("this is your EQUANCI ITOG -> %d\n , POW -> %d", itog, final);
    if (final == itog) return 1;
    return 0;
}


int main (void)
{
    int x, b;
    scanf("%d", &x);
    b = x;
    while (x % 10 != 0)
    {
        printf("this is your -> %d\n", x%10);
        x = x / 10; 
    }

    printf("\n");
    printf("\n");
    printf("\n");
    if (recheck(b) == 1) 
        printf("\nYES BRAH!");
}