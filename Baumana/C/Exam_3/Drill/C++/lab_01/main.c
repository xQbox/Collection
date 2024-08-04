#include <stdio.h>

int main(void)
{
    int n;
    double sum = 0;
    scanf("%d", &n);
    while (n)
    {
        sum += 1 / n--;  
    }
    printf("%f", sum);
    return 0;
}