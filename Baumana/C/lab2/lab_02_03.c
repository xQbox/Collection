#include <stdio.h>
#include <math.h>
/*Вставить в исходный массив после каждого положительного элемента реверс
этого же элемента. Ситуацию, когда массив после операции не изменился, оши-
бочной не считать */
int check_nmb(int n)
{
    int x;
    while (scanf("%d", &x) != 1)
    {
        printf("wrong input\n");
        printf("Write some number of Array[%d]: ", n+1);
        while(getchar() != '\n');
    }
    return x;
}


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

void print_array(int A[], int N)
{
    for (int i = 0; i <= N; i ++)
        {
        printf("%5d", A[i]);
        if(((i+1) % 5 == 0))
            printf("\n");
        }
    printf("\n"); 
}
int rev_exp(int n)
{
    int top, count, res;
    int A[100] = {0};
    top = 0;
    count = 0;
    res = 0;
    if (n / 10 == 0) return n;
    while (1)
    {
        A[top] = n%10;
        top += 1;
        count += 1;
        n /= 10;
        if (n == 0) 
        {   
            count -= 1;
            break;
        }
    }

    for (int i = 0; i < top; i++)
    {
        res += A[i] * pow(10, count);
        count -= 1;
    }
    return res;
}
int main(void)
{
    int top, pointer, i, x;
    top = i = pointer = 0;
    pointer = ask_int();
    int A[20] = {0};
    while(1)
    {   
        if (i == pointer) break;
        printf("Write some number of Array[%d]: ", i+1);
        x = check_nmb(i);
        A[top] = x;
        i += 1;
        top += 1;
    }
    i = 0;
    int count, k;
    count = k = 0;
    top = pointer * 2;
    while(i < pointer * 2)
    {
        while (k < pointer)
        {
            if (A[k] < 0 || A[k] == 0)
                count += 1;
            k += 1;
        }
        if (A[i] > 0) // зациклить алгоритм переноса элемента массива на один вправо(циклический сдвиг)
        {
            int k = 20;
            while (k > i+1)
            {
                A[k] = A[k - 1];
                k -= 1;
            }
            A[i + 1] = rev_exp(A[i]);
            i += 2;
        }
        else
        {
            i += 1;
        }
    }
    top = top - (count + 1);
    print_array(A, top);
    return 0;
}