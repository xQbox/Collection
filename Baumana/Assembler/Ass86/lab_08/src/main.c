#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <io.h>
#include <windows.h>
#include "myerrors.h"
#include "math.h"

#include "method.h"

#define PISHORT 3.14
#define PILONG 3.131596

int GetAssemblerTime();

void getErrorValue();

int GetCTime()
{
     printf("Write float number below:\n");
    float fInputed = 0;
    if ((scanf("%f", &fInputed) == 0)) 
        return -1;
    
    printf("Write double number below:\n");
    double dInputed = 0;
    if ((scanf("%lf", &dInputed) == 0)) 
        return -2;

// Calculation speed of summarize float values 
    size_t n = 0, count = 10000000;
    clock_t start, end;
    double MUL, SUM;

    SUM = 0.0 ;
    while (n < count)
    {
        start = clock();
     
        fInputed = fInputed + 12.321;
        fInputed = fInputed + 12.321;
        fInputed = fInputed + 12.321;
        fInputed = fInputed + 12.321;
        fInputed = fInputed + 12.321;
        fInputed = fInputed + 12.321;
        fInputed = fInputed + 12.321;
        fInputed = fInputed + 12.321;
        fInputed = fInputed + 12.321;
        fInputed = fInputed + 12.321;
     
        end = clock() - start;
        SUM += end;
        ++n;
    }
    SUM /= count;

    n = 0;

    MUL = 0.0 ;
    while (n < count)
    {
        start = clock();
     
        fInputed = fInputed + 12.321;
        fInputed = fInputed + 12.321;
        fInputed = fInputed + 12.321;
        fInputed = fInputed + 12.321;
        fInputed = fInputed + 12.321;
        fInputed = fInputed + 12.321;
        fInputed = fInputed + 12.321;
        fInputed = fInputed + 12.321;
        fInputed = fInputed + 12.321;
        fInputed = fInputed + 12.321;
     
        end = clock() - start;
        MUL += end;
        ++n;
    }
    MUL /= count;
    
    printf("Results :\n");
    printf("1) SUM %lf\n", SUM);
    printf("2) MUL %lf\n", MUL);
    
    n = 0;
    
    SUM = 0.0 ;
    while (n < count)
    {
        start = clock();
     
        dInputed = dInputed + 12.3213212;
        dInputed = dInputed + 12.3213212;
        dInputed = dInputed + 12.3213212;
        dInputed = dInputed + 12.3213212;
        dInputed = dInputed + 12.3213212;
        dInputed = dInputed + 12.3213212;
        dInputed = dInputed + 12.3213212;
        dInputed = dInputed + 12.3213212;
        dInputed = dInputed + 12.3213212;
        dInputed = dInputed + 12.3213212;
     
        end = clock() - start;
        SUM += end;
        ++n;
    }
    SUM /= count;

    n = 0;

    MUL = 0.0 ;
    while (n < count)
    {
        start = clock();
     
        dInputed = dInputed + 12.3213212;
        dInputed = dInputed + 12.3213212;
        dInputed = dInputed + 12.3213212;
        dInputed = dInputed + 12.3213212;
        dInputed = dInputed + 12.3213212;
        dInputed = dInputed + 12.3213212;
        dInputed = dInputed + 12.3213212;
        dInputed = dInputed + 12.3213212;
        dInputed = dInputed + 12.3213212;
        dInputed = dInputed + 12.3213212;
     
        end = clock() - start;
        MUL += end;
        ++n;
    }
    MUL /= count;

    printf("Results :\n");
    printf("1) SUM %lf\n", SUM);
    printf("2) MUL %lf\n", MUL);
    return 0;
}

int GetAssTime()
{
    // printf("Write double number below:\n");
    double dInputed = 3.12341221;
    size_t n = 0, count = 10000000;
    clock_t start, end;
    double MUL, SUM;

    SUM = 0.0 ;
    while (n < count)
    {
        start = clock();
        __asm{
            fld dInputed
            fld dInputed
            fadd
        } 
        end = clock() - start;
        SUM += end;
        ++n;
    }
    SUM /= count;

    n = 0;

    MUL = 0.0 ;
    while (n < count)
    {
        start = clock();
        __asm{
            fld dInputed
            fld dInputed
            fmul
        }
     
        end = clock() - start;
        MUL += end;
        ++n;
    }
    MUL /= count;

    printf("Results :\n");
    printf("1) SUM %lf\n", SUM);
    printf("2) MUL %lf\n", MUL);

    
    start =  clock();
    __asm{
        push rax
        push rbx
        push rdx
        push rcx
        push rsi
        push count
        push dInputed
    }
    GetAssemblerTime();
    __asm{
        add rsp, 16
        pop rsi
        pop rcx
        pop rdx
        pop rbx
        pop rax
    }
    end = clock() - start;

    printf("3) Funcion result %lf", (double) end);
    return 0;
}

int getSinusTime()
{
    printf("oke\n");
    double dresult = sin(PISHORT);
    double dhalfResult = sin((double) PISHORT / 2.0);
    printf("PISHORT \n1) sin(x) %lf\n2) sin(x/2) %lf\n", dresult, dhalfResult);

    dresult = sin(PILONG);
    dhalfResult = sin((double) PILONG / 2.0);
    printf("PILONG \n1) sin(x) %lf\n2) sin(x/2) %lf\n", dresult, dhalfResult);

    dhalfResult = 2.0;    
    __asm{
        fldpi 
        fsin 
        fst dresult
        fld dhalfResult
        fldpi 
        fdiv
        fsin 
        fst dhalfResult
    }
    printf("FPU \n1) sin(x) %lf\n2) sin(x/2) %lf\n", dresult, dhalfResult);

    return 0;
}



int main(void)
{
    int rc = 0;
    rc = GetCTime();
    if (rc)
    {
        // getErrorValue(rc);
        return ERR_CTIME;
    }

    rc = GetAssTime();
    if (rc)
    {
        // getErrorValue(rc);
        return ERR_ASSTIME;
    }

    rc = getSinusTime();

    rc = method();
    if (rc)
    {
        return -3;
    }

    return 0;
}

