#include <stdio.h>
#include <string.h>


int main(void)
{
    FILE *f;
    f = fopen("new", "r");
    int num;
    char M[3][50];
    int i, k ;
    i = k =0;
    while(!feof(f))
    {   
        while(fscanf(f, "%d", &num) == 1)
        {
            M[i][k] = num;
            k +=1;
            if (num == '\n')
            {
                i += 1;
            }
            printf("%d", M[i][k]);
        }   


    }
    return 0;
}
