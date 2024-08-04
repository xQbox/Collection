#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    size_t n = 3, m = 2;
    double **matrix = malloc(sizeof(double *) * n + sizeof(double) * n * m);
    double *start = (double *) ((char *) matrix + n * sizeof(double *));
    for (size_t i = 0; i < n; ++i)
    {
        matrix[i] = start + i * m * sizeof(double);  
    }
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t k = 0; k < m; ++k)
        {
            matrix[i][k] = i + 1;
        }
    }

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t k = 0; k < m; ++k)
        {
            printf("%lf ", matrix[i][k]);
        }
        printf("\n");
    }
    return 0;
}