#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

double func(double *value)
{
    double result;
    double digit = -5, tmp = *value;
    __asm{
        fld tmp 
        fld st(0) 
        fmul 
        fld digit
        fadd 
        fsin 
        fst result
    }
    return (result * 2);
}

int readIteration(size_t *lpValue)
{
    printf("Write Amount of Iterations below : \n");

    int iTmp = 0;
    int rc = scanf("%d", &iTmp);
    if (!rc)
        return -1;
    if (iTmp < 0)
        return -2;

    *lpValue = iTmp;
    return 0;
}


int readSection(double *lpStart, double *lpEnd)
{
    printf("Write Section (Start, End) position below : \n");

    double iTmp = 0.;
    int rc = scanf("%lf", &iTmp);
    if (!rc)
        return -1;
    
    *lpStart = iTmp;
    
    rc = scanf("%lf", &iTmp);
    if (!rc)
        return -1;
    
    if (iTmp < *lpStart)
    {
        return -2;
    }

    *lpEnd = iTmp;

    return 0;
}
int findRoot(size_t *lpIterations, double *lpStart, double *lpEnd, double *lpRoot)
{
    double tmpRoot;
    double fa = func(lpStart);
    double fb = func(lpEnd);
    double fx, x;

    if ((fa * fb) > 0)
    {
        return -1;
    }

    for (int i = 0; i < *lpIterations; ++i)
    {
        x = *lpStart + (*lpEnd - *lpStart) / 2;
        fx = func(&x);
        fa = func(lpStart);

        if ((fx * fa) < 0)
        {
            *lpEnd = x;
        }
        else
        {
            *lpStart = x;
        }
    }

    tmpRoot = *lpStart + (*lpEnd - *lpStart) / 2;
    *lpRoot = tmpRoot;

    return 0;
}

int method()
{
    int rc = 0;
    size_t sIteration = 0;
    double dStartA = 0, dEndB = 0, root = 0; 

    rc = readIteration(&sIteration);
    if (rc)
    {
        return -1;
    }

    rc = readSection(&dStartA, &dEndB);
    if (rc)
    {
        return -2;
    }
   
    rc = findRoot(&sIteration, &dStartA, &dEndB, &root);
    if (rc)
    {
        return -3;
    }
    
    printf("Root %lf\n", root);
    
    return 0;
}