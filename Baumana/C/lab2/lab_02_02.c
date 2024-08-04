#include <stdio.h>
#include <math.h>
// 3. Сформировать и вывести на экран новый массив, в который скопировать эле-
// менты исходного массива, которые являются числами Армстронга.

int ask_int()
{   int res;
    while (1)
    {   
        printf("Write size of Array: ");
        if (scanf("%d", &res) == 1 && res > 0 && res < 11) break;
        while(getchar() != '\n');   
    }   
    return res;
}

int check_nmb(int n)
{   
    int x;
    while (scanf("%d" , &x) != 1)
    {
       printf("Wrong input");
       printf("Write numbers of Array[%d]: ", n+1);
       while(getchar() != '\n');
    }
    return x;
}
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
        }
        res = n % 10;
        final += pow(res, flag);
        n /= 10;
    }
    if (final == itog) return 1;
    return 0;
}


void print_arr(int A[], int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("%5d", A[i]);
    }
    printf("\n");
}

int main(void)
{
    int B[10] = {0};
    int M[10] = {0};
    int x, i = 0, top, res;
    res = ask_int();

    while(1)
    {   
        if (i == res) break;
        printf("Write array numbers[%d] -> ", (i + 1));
        x = check_nmb(i);
        if (recheck(x))
        {
            M[top] = x;
            top += 1;
        }
        B[i] = x;
        i ++;
    }
    print_arr(B, i);
    printf("\n");
    print_arr(M, top);
    return 0;
}